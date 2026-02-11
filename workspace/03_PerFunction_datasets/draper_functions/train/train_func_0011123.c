tb_cfg_read_raw(struct tb_ctl *ctl, void *buffer,
		u64 route, u32 port, enum tb_cfg_space space,
		u32 offset, u32 length, int timeout_msec)
{
	struct tb_cfg_result res = { 0 };
	struct cfg_read_pkg request = {
		.header = make_header(route),
		.addr = {
			.port = port,
			.space = space,
			.offset = offset,
			.length = length,
		},
	};
	struct cfg_write_pkg reply;

	res.err = tb_ctl_tx(ctl, &request, sizeof(request), TB_CFG_PKG_READ);
	if (res.err)
		return res;

	res = tb_ctl_rx(ctl, &reply, 12 + 4 * length, timeout_msec, route,
			TB_CFG_PKG_READ);
	if (res.err)
		return res;

	res.response_port = reply.addr.port;
	res.err = check_config_address(reply.addr, space, offset, length);
	if (!res.err)
		memcpy(buffer, &reply.data, 4 * length);
	return res;
}
