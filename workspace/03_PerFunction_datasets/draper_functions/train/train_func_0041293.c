bnx2x_is_sfp_module_plugged(struct bnx2x_phy *phy,
				       struct link_params *params)
{
	struct bnx2x *bp = params->bp;
	u8 gpio_num, gpio_port;
	u32 gpio_val;
	if (bnx2x_get_mod_abs_int_cfg(bp, params->chip_id,
				      params->shmem_base, params->port,
				      &gpio_num, &gpio_port) != 0)
		return 0;
	gpio_val = bnx2x_get_gpio(bp, gpio_num, gpio_port);


	if (gpio_val == 0)
		return 1;
	else
		return 0;
}
