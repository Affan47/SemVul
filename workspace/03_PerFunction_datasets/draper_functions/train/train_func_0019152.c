bnx2x_sfp_tx_fault_detection(struct bnx2x_phy *phy,
					 struct link_params *params,
					 struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;
	u32 cfg_pin, value = 0;
	u8 led_change, port = params->port;


	cfg_pin = (REG_RD(bp, params->shmem_base + offsetof(struct shmem_region,
			  dev_info.port_hw_config[port].e3_cmn_pin_cfg)) &
		   PORT_HW_CFG_E3_TX_FAULT_MASK) >>
		  PORT_HW_CFG_E3_TX_FAULT_SHIFT;

	if (bnx2x_get_cfg_pin(bp, cfg_pin, &value)) {
		DP(NETIF_MSG_LINK, "Failed to read pin 0x%02x\n", cfg_pin);
		return;
	}

	led_change = bnx2x_analyze_link_error(params, vars, value,
					      PHY_SFP_TX_FAULT_FLAG,
					      LINK_STATUS_SFP_TX_FAULT, 1);

	if (led_change) {

		u8 led_mode;

		if (vars->phy_flags & PHY_SFP_TX_FAULT_FLAG) {
			led_mode = MISC_REGISTERS_GPIO_HIGH;
			vars->link_status |= LINK_STATUS_SFP_TX_FAULT;
		} else {
			led_mode = MISC_REGISTERS_GPIO_LOW;
			vars->link_status &= ~LINK_STATUS_SFP_TX_FAULT;
		}


		if (!(phy->flags & FLAGS_SFP_NOT_APPROVED)) {
			DP(NETIF_MSG_LINK, "Change TX_Fault LED: ->%x\n",
			   led_mode);
			bnx2x_set_e3_module_fault_led(params, led_mode);
		}
	}
}
