ixgb_get_eeprom_data(struct ixgb_hw *hw)
{
	u16 i;
	u16 checksum = 0;
	struct ixgb_ee_map_type *ee_map;

	ENTER();

	ee_map = (struct ixgb_ee_map_type *)hw->eeprom;

	pr_debug("Reading eeprom data\n");
	for (i = 0; i < IXGB_EEPROM_SIZE ; i++) {
		u16 ee_data;
		ee_data = ixgb_read_eeprom(hw, i);
		checksum += ee_data;
		hw->eeprom[i] = cpu_to_le16(ee_data);
	}

	if (checksum != (u16) EEPROM_SUM) {
		pr_debug("Checksum invalid\n");


		ee_map->init_ctrl_reg_1 = cpu_to_le16(EEPROM_ICW1_SIGNATURE_CLEAR);
		return false;
	}

	if ((ee_map->init_ctrl_reg_1 & cpu_to_le16(EEPROM_ICW1_SIGNATURE_MASK))
		 != cpu_to_le16(EEPROM_ICW1_SIGNATURE_VALID)) {
		pr_debug("Signature invalid\n");
		return false;
	}

	return true;
}
