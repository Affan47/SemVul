mtnic_query_mac(struct mtnic *mtnic)
{
	int err = 0;
	int i;
	u64 result;

	for (i = 0; i < mtnic->fw.num_ports; i++) {
		DO_QUERY_CAP(MTNIC_IF_CAP_DEFAULT_MAC, i + 1, mtnic->fw.mac[i]);
	}

	return 0;
}
