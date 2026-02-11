mlx4_ib_mcg_detach(struct ib_qp *ibqp, union ib_gid *gid, u16 lid)
{
	int err;
	struct mlx4_ib_dev *mdev = to_mdev(ibqp->device);
	struct mlx4_dev *dev = mdev->dev;
	struct mlx4_ib_qp *mqp = to_mqp(ibqp);
	struct net_device *ndev;
	struct mlx4_ib_gid_entry *ge;
	struct mlx4_flow_reg_id reg_id = {0, 0};
	enum mlx4_protocol prot =  MLX4_PROT_IB_IPV6;

	if (mdev->dev->caps.steering_mode ==
	    MLX4_STEERING_MODE_DEVICE_MANAGED) {
		struct mlx4_ib_steering *ib_steering;

		mutex_lock(&mqp->mutex);
		list_for_each_entry(ib_steering, &mqp->steering_rules, list) {
			if (!memcmp(ib_steering->gid.raw, gid->raw, 16)) {
				list_del(&ib_steering->list);
				break;
			}
		}
		mutex_unlock(&mqp->mutex);
		if (&ib_steering->list == &mqp->steering_rules) {
			pr_err("Couldn't find reg_id for mgid. Steering rule is left attached\n");
			return -EINVAL;
		}
		reg_id = ib_steering->reg_id;
		kfree(ib_steering);
	}

	err = mlx4_multicast_detach(mdev->dev, &mqp->mqp, gid->raw,
				    prot, reg_id.id);
	if (err)
		return err;

	if (mlx4_is_bonded(dev)) {
		err = mlx4_multicast_detach(mdev->dev, &mqp->mqp, gid->raw,
					    prot, reg_id.mirror);
		if (err)
			return err;
	}

	mutex_lock(&mqp->mutex);
	ge = find_gid_entry(mqp, gid->raw);
	if (ge) {
		spin_lock_bh(&mdev->iboe.lock);
		ndev = ge->added ? mdev->iboe.netdevs[ge->port - 1] : NULL;
		if (ndev)
			dev_hold(ndev);
		spin_unlock_bh(&mdev->iboe.lock);
		if (ndev)
			dev_put(ndev);
		list_del(&ge->list);
		kfree(ge);
	} else
		pr_warn("could not find mgid entry\n");

	mutex_unlock(&mqp->mutex);

	return 0;
}
