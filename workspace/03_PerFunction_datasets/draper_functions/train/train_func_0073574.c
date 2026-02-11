mlx4_ib_multiplex_sa_handler(struct ib_device *ibdev, int port,
		int slave, struct ib_sa_mad *sa_mad)
{
	int ret = 0;


	switch (be16_to_cpu(sa_mad->mad_hdr.attr_id)) {
	case IB_SA_ATTR_MC_MEMBER_REC:
		ret = mlx4_ib_mcg_multiplex_handler(ibdev, port, slave, sa_mad);
		break;
	default:
		break;
	}
	return ret;
}
