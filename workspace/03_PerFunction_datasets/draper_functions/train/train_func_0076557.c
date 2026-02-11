bnx2x_warpcore_power_module(struct link_params *params,
					u8 power)
{
	u32 pin_cfg;
	struct bnx2x *bp = params->bp;

	pin_cfg = (REG_RD(bp, params->shmem_base +
			  offsetof(struct shmem_region,
			dev_info.port_hw_config[params->port].e3_sfp_ctrl)) &
			PORT_HW_CFG_E3_PWR_DIS_MASK) >>
			PORT_HW_CFG_E3_PWR_DIS_SHIFT;

	if (pin_cfg == PIN_CFG_NA)
		return;
	DP(NETIF_MSG_LINK, "Setting SFP+ module power to %d using pin cfg %d\n",
		       power, pin_cfg);


	bnx2x_set_cfg_pin(bp, pin_cfg, power ^ 1);
}
