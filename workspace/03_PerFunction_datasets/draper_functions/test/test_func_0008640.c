e1000_init_mac_params_82540(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	s32 ret_val = E1000_SUCCESS;

	DEBUGFUNC("e1000_init_mac_params_82540");


	switch (hw->device_id) {
	case E1000_DEV_ID_82545EM_FIBER:
	case E1000_DEV_ID_82545GM_FIBER:
	case E1000_DEV_ID_82546EB_FIBER:
	case E1000_DEV_ID_82546GB_FIBER:
		hw->phy.media_type = e1000_media_type_fiber;
		break;
	case E1000_DEV_ID_82545GM_SERDES:
	case E1000_DEV_ID_82546GB_SERDES:
		hw->phy.media_type = e1000_media_type_internal_serdes;
		break;
	default:
		hw->phy.media_type = e1000_media_type_copper;
		break;
	}


	mac->mta_reg_count = 128;

	mac->rar_entry_count = E1000_RAR_ENTRIES;


	mac->ops.get_bus_info = e1000_get_bus_info_pci_generic;

	mac->ops.set_lan_id = e1000_set_lan_id_multi_port_pci;

	mac->ops.reset_hw = e1000_reset_hw_82540;

	mac->ops.init_hw = e1000_init_hw_82540;

	mac->ops.setup_link = e1000_setup_link_generic;

	mac->ops.setup_physical_interface =
	        (hw->phy.media_type == e1000_media_type_copper)
	                ? e1000_setup_copper_link_82540
	                : e1000_setup_fiber_serdes_link_82540;

	switch (hw->phy.media_type) {
	case e1000_media_type_copper:
		mac->ops.check_for_link = e1000_check_for_copper_link_generic;
		break;
	case e1000_media_type_fiber:
		mac->ops.check_for_link = e1000_check_for_fiber_link_generic;
		break;
	case e1000_media_type_internal_serdes:
		mac->ops.check_for_link = e1000_check_for_serdes_link_generic;
		break;
	default:
		ret_val = -E1000_ERR_CONFIG;
		goto out;
		break;
	}

	mac->ops.get_link_up_info =
	        (hw->phy.media_type == e1000_media_type_copper)
	                ? e1000_get_speed_and_duplex_copper_generic
	                : e1000_get_speed_and_duplex_fiber_serdes_generic;

	mac->ops.update_mc_addr_list = e1000_update_mc_addr_list_generic;

	mac->ops.write_vfta = e1000_write_vfta_generic;

	mac->ops.clear_vfta = e1000_clear_vfta_generic;

	mac->ops.mta_set = e1000_mta_set_generic;

	mac->ops.read_mac_addr = e1000_read_mac_addr_82540;

	mac->ops.id_led_init = e1000_id_led_init_generic;

	mac->ops.setup_led = e1000_setup_led_generic;

	mac->ops.cleanup_led = e1000_cleanup_led_generic;

	mac->ops.led_on = e1000_led_on_generic;
	mac->ops.led_off = e1000_led_off_generic;

	mac->ops.clear_hw_cntrs = e1000_clear_hw_cntrs_82540;

out:
	return ret_val;
}
