e1000e_init_mac_params_ich8lan(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;


	hw->phy.media_type = e1000_media_type_copper;


	mac->mta_reg_count = 32;

	mac->rar_entry_count = E1000_ICH_RAR_ENTRIES;
	if (mac->type == e1000_ich8lan)
		mac->rar_entry_count--;

	mac->asf_firmware_present = true;

	mac->arc_subsystem_valid = true;


	mac->ops.get_bus_info = e1000e_get_bus_info_ich8lan;

	mac->ops.set_lan_id = e1000e_set_lan_id_single_port;

	mac->ops.reset_hw = e1000e_reset_hw_ich8lan;

	mac->ops.init_hw = e1000e_init_hw_ich8lan;

	mac->ops.setup_link = e1000e_setup_link_ich8lan;

	mac->ops.setup_physical_interface = e1000e_setup_copper_link_ich8lan;

	mac->ops.check_for_link = e1000e_check_for_copper_link_ich8lan;

	mac->ops.check_mng_mode = e1000e_check_mng_mode_ich8lan;

	mac->ops.get_link_up_info = e1000e_get_link_up_info_ich8lan;

	mac->ops.update_mc_addr_list = e1000e_update_mc_addr_list_generic;

	mac->ops.mta_set = e1000e_mta_set_generic;

	mac->ops.clear_hw_cntrs = e1000e_clear_hw_cntrs_ich8lan;


	switch (mac->type) {
	case e1000_ich8lan:
	case e1000_ich9lan:
	case e1000_ich10lan:

		mac->ops.id_led_init = e1000e_id_led_init;

		mac->ops.blink_led = e1000e_blink_led;

		mac->ops.setup_led = e1000e_setup_led_generic;

		mac->ops.cleanup_led = e1000e_cleanup_led_ich8lan;

		mac->ops.led_on = e1000e_led_on_ich8lan;
		mac->ops.led_off = e1000e_led_off_ich8lan;
		break;
	case e1000_pchlan:

		mac->ops.id_led_init = e1000e_id_led_init_pchlan;

		mac->ops.setup_led = e1000e_setup_led_pchlan;

		mac->ops.cleanup_led = e1000e_cleanup_led_pchlan;

		mac->ops.led_on = e1000e_led_on_pchlan;
		mac->ops.led_off = e1000e_led_off_pchlan;
		break;
	default:
		break;
	}


	if (mac->type == e1000_ich8lan)
		e1000e_set_kmrn_lock_loss_workaround_ich8lan(hw, true);


	return E1000_SUCCESS;
}
