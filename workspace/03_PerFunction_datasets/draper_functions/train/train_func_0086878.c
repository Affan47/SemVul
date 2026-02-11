qib_multicast_detach(struct ib_qp *ibqp, union ib_gid *gid, u16 lid)
{
	struct qib_qp *qp = to_iqp(ibqp);
	struct qib_ibdev *dev = to_idev(ibqp->device);
	struct qib_ibport *ibp = to_iport(ibqp->device, qp->port_num);
	struct qib_mcast *mcast = NULL;
	struct qib_mcast_qp *p, *tmp, *delp = NULL;
	struct rb_node *n;
	int last = 0;
	int ret;

	if (ibqp->qp_num <= 1 || qp->state == IB_QPS_RESET)
		return -EINVAL;

	spin_lock_irq(&ibp->lock);


	n = ibp->mcast_tree.rb_node;
	while (1) {
		if (n == NULL) {
			spin_unlock_irq(&ibp->lock);
			return -EINVAL;
		}

		mcast = rb_entry(n, struct qib_mcast, rb_node);
		ret = memcmp(gid->raw, mcast->mgid.raw,
			     sizeof(union ib_gid));
		if (ret < 0)
			n = n->rb_left;
		else if (ret > 0)
			n = n->rb_right;
		else
			break;
	}


	list_for_each_entry_safe(p, tmp, &mcast->qp_list, list) {
		if (p->qp != qp)
			continue;


		list_del_rcu(&p->list);
		mcast->n_attached--;
		delp = p;


		if (list_empty(&mcast->qp_list)) {
			rb_erase(&mcast->rb_node, &ibp->mcast_tree);
			last = 1;
		}
		break;
	}

	spin_unlock_irq(&ibp->lock);

	if (!delp)
		return -EINVAL;


	wait_event(mcast->wait, atomic_read(&mcast->refcount) <= 1);
	qib_mcast_qp_free(delp);

	if (last) {
		atomic_dec(&mcast->refcount);
		wait_event(mcast->wait, !atomic_read(&mcast->refcount));
		qib_mcast_free(mcast);
		spin_lock_irq(&dev->n_mcast_grps_lock);
		dev->n_mcast_grps_allocated--;
		spin_unlock_irq(&dev->n_mcast_grps_lock);
	}
	return 0;
}
