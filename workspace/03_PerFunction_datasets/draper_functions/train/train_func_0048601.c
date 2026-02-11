mtnic_query_num_ports(struct mtnic *mtnic)
{
	int err = 0;
	u64 result;

	DO_QUERY_CAP(MTNIC_IF_CAP_NUM_PORTS, 0, mtnic->fw.num_ports);

	return 0;
}
