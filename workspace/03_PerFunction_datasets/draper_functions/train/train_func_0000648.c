tb_cfg_print_error(struct tb_ctl *ctl,
			       const struct tb_cfg_result *res)
{
	WARN_ON(res->err != 1);
	switch (res->tb_error) {
	case TB_CFG_ERROR_PORT_NOT_CONNECTED:


		return;
	case TB_CFG_ERROR_INVALID_CONFIG_SPACE:


		tb_ctl_WARN(ctl,
			"CFG_ERROR(%llx:%x): Invalid config space of offset\n",
			res->response_route, res->response_port);
		return;
	case TB_CFG_ERROR_NO_SUCH_PORT:


		tb_ctl_WARN(ctl, "CFG_ERROR(%llx:%x): Invalid port\n",
			res->response_route, res->response_port);
		return;
	case TB_CFG_ERROR_LOOP:
		tb_ctl_WARN(ctl, "CFG_ERROR(%llx:%x): Route contains a loop\n",
			res->response_route, res->response_port);
		return;
	default:

		tb_ctl_WARN(ctl, "CFG_ERROR(%llx:%x): Unknown error\n",
			res->response_route, res->response_port);
		return;
	}
}
