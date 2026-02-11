__mlx4_ib_create_flow(struct ib_qp *qp, struct ib_flow_attr *flow_attr,
			  int domain,
			  enum mlx4_net_trans_promisc_mode flow_type,
			  u64 *reg_id)
{
	int ret, i;
	int size = 0;
	void *ib_flow;
	struct mlx4_ib_dev *mdev = to_mdev(qp->device);
	struct mlx4_cmd_mailbox *mailbox;
	struct mlx4_net_trans_rule_hw_ctrl *ctrl;
	int default_flow;

	static const u16 __mlx4_domain[] = {
		[IB_FLOW_DOMAIN_USER] = MLX4_DOMAIN_UVERBS,
		[IB_FLOW_DOMAIN_ETHTOOL] = MLX4_DOMAIN_ETHTOOL,
		[IB_FLOW_DOMAIN_RFS] = MLX4_DOMAIN_RFS,
		[IB_FLOW_DOMAIN_NIC] = MLX4_DOMAIN_NIC,
	};

	if (flow_attr->priority > MLX4_IB_FLOW_MAX_PRIO) {
		pr_err("Invalid priority value %d\n", flow_attr->priority);
		return -EINVAL;
	}

	if (domain >= IB_FLOW_DOMAIN_NUM) {
		pr_err("Invalid domain value %d\n", domain);
		return -EINVAL;
	}

	if (mlx4_map_sw_to_hw_steering_mode(mdev->dev, flow_type) < 0)
		return -EINVAL;

	mailbox = mlx4_alloc_cmd_mailbox(mdev->dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	ctrl = mailbox->buf;

	ctrl->prio = cpu_to_be16(__mlx4_domain[domain] |
				 flow_attr->priority);
	ctrl->type = mlx4_map_sw_to_hw_steering_mode(mdev->dev, flow_type);
	ctrl->port = flow_attr->port;
	ctrl->qpn = cpu_to_be32(qp->qp_num);

	ib_flow = flow_attr + 1;
	size += sizeof(struct mlx4_net_trans_rule_hw_ctrl);

	default_flow = __mlx4_ib_default_rules_match(qp, flow_attr);
	if (default_flow >= 0) {
		ret = __mlx4_ib_create_default_rules(
				mdev, qp, default_table + default_flow,
				mailbox->buf + size);
		if (ret < 0) {
			mlx4_free_cmd_mailbox(mdev->dev, mailbox);
			return -EINVAL;
		}
		size += ret;
	}
	for (i = 0; i < flow_attr->num_of_specs; i++) {
		ret = parse_flow_attr(mdev->dev, qp->qp_num, ib_flow,
				      mailbox->buf + size);
		if (ret < 0) {
			mlx4_free_cmd_mailbox(mdev->dev, mailbox);
			return -EINVAL;
		}
		ib_flow += ((union ib_flow_spec *) ib_flow)->size;
		size += ret;
	}

	ret = mlx4_cmd_imm(mdev->dev, mailbox->dma, reg_id, size >> 2, 0,
			   MLX4_QP_FLOW_STEERING_ATTACH, MLX4_CMD_TIME_CLASS_A,
			   MLX4_CMD_WRAPPED);
	if (ret == -ENOMEM)
		pr_err("mcg table is full. Fail to register network rule.\n");
	else if (ret == -ENXIO)
		pr_err("Device managed flow steering is disabled. Fail to register network rule.\n");
	else if (ret)
		pr_err("Invalid argumant. Fail to register network rule.\n");

	mlx4_free_cmd_mailbox(mdev->dev, mailbox);
	return ret;
}
