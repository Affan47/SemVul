igb_init_mac_params_82575(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	struct e1000_dev_spec_82575 *dev_spec = &hw->dev_spec._82575;


	mac->mta_reg_count = 128;

	mac->uta_reg_count = (hw->mac.type == e1000_82575) ? 0 : 128;

	switch (mac->type) {
	case e1000_82576:
		mac->rar_entry_count = E1000_RAR_ENTRIES_82576;
		break;
	case e1000_82580:
		mac->rar_entry_count = E1000_RAR_ENTRIES_82580;
		break;
	case e1000_i350:
	case e1000_i354:
		mac->rar_entry_count = E1000_RAR_ENTRIES_I350;
		break;
	default:
		mac->rar_entry_count = E1000_RAR_ENTRIES_82575;
		break;
	}

	if (mac->type >= e1000_82580)
		mac->ops.reset_hw = igb_reset_hw_82580;
	else
		mac->ops.reset_hw = igb_reset_hw_82575;

	if (mac->type >= e1000_i210) {
		mac->ops.acquire_swfw_sync = igb_acquire_swfw_sync_i210;
		mac->ops.release_swfw_sync = igb_release_swfw_sync_i210;

	} else {
		mac->ops.acquire_swfw_sync = igb_acquire_swfw_sync_82575;
		mac->ops.release_swfw_sync = igb_release_swfw_sync_82575;
	}

	if ((hw->mac.type == e1000_i350) || (hw->mac.type == e1000_i354))
		mac->ops.write_vfta = igb_write_vfta_i350;
	else
		mac->ops.write_vfta = igb_write_vfta;


	mac->asf_firmware_present = true;

	mac->arc_subsystem_valid =
		(rd32(E1000_FWSM) & E1000_FWSM_MODE_MASK)
			? true : false;

	if (mac->type >= e1000_i350)
		dev_spec->eee_disable = false;
	else
		dev_spec->eee_disable = true;

	if (mac->type >= e1000_i210)
		dev_spec->clear_semaphore_once = true;

	mac->ops.setup_physical_interface =
		(hw->phy.media_type == e1000_media_type_copper)
			? igb_setup_copper_link_82575
			: igb_setup_serdes_link_82575;

	if (mac->type == e1000_82580) {
		switch (hw->device_id) {

		case E1000_DEV_ID_DH89XXCC_SGMII:
		case E1000_DEV_ID_DH89XXCC_SERDES:
		case E1000_DEV_ID_DH89XXCC_BACKPLANE:
		case E1000_DEV_ID_DH89XXCC_SFP:
			break;
		default:
			hw->dev_spec._82575.mas_capable = true;
			break;
		}
	}
	return 0;
}
