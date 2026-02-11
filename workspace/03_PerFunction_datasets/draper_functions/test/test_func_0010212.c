update_mcg_macs(struct mlx4_ib_dev *dev, struct mlx4_ib_qp *qp)
{
	struct mlx4_ib_gid_entry *ge, *tmp;

	list_for_each_entry_safe(ge, tmp, &qp->gid_list, list) {
		if (!ge->added && mlx4_ib_add_mc(dev, qp, &ge->gid)) {
			ge->added = 1;
			ge->port = qp->port;
		}
	}
}
