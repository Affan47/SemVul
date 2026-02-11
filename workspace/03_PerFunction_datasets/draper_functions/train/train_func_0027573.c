tsi568_route_get_entry(struct rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table, u16 route_destid, u8 *route_port)
{
	int ret = 0;
	u32 result;

	if (table == RIO_GLOBAL_TABLE) {
		rio_mport_write_config_32(mport, destid, hopcount,
					SPBC_ROUTE_CFG_DESTID, route_destid);
		rio_mport_read_config_32(mport, destid, hopcount,
					SPBC_ROUTE_CFG_PORT, &result);
	} else {
		rio_mport_write_config_32(mport, destid, hopcount,
					SPP_ROUTE_CFG_DESTID(table),
					route_destid);
		rio_mport_read_config_32(mport, destid, hopcount,
					SPP_ROUTE_CFG_PORT(table), &result);
	}

	*route_port = result;
	if (*route_port > 15)
		ret = -1;

	return ret;
}
