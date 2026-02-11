tb_cfg_get_upstream_port(struct tb_ctl *ctl, u64 route)
{
	u32 dummy;
	struct tb_cfg_result res = tb_cfg_read_raw(ctl, &dummy, route, 0,
						   TB_CFG_SWITCH, 0, 1,
						   TB_CFG_DEFAULT_TIMEOUT);
	if (res.err == 1)
		return -EIO;
	if (res.err)
		return res.err;
	return res.response_port;
}
