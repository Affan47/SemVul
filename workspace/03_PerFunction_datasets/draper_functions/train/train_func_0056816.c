e1000_validate_eeprom_checksum(struct e1000_hw *hw)
{
    uint16_t checksum = 0;
    uint16_t i, eeprom_data;

    DEBUGFUNC("e1000_validate_eeprom_checksum");

    if ((hw->mac_type == e1000_82573) &&
        (e1000_is_onboard_nvm_eeprom(hw) == FALSE)) {


        e1000_read_eeprom(hw, 0x10, 1, &eeprom_data);
        if ((eeprom_data & 0x10) == 0) {


            e1000_read_eeprom(hw, 0x23, 1, &eeprom_data);
            if ((eeprom_data & 0x8000) == 0) {
                eeprom_data |= 0x8000;
                e1000_write_eeprom(hw, 0x23, 1, &eeprom_data);
                e1000_update_eeprom_checksum(hw);
            }
        }
    }

    if (hw->mac_type == e1000_ich8lan) {


        e1000_read_eeprom(hw, 0x19, 1, &eeprom_data);
        if ((eeprom_data & 0x40) == 0) {
            eeprom_data |= 0x40;
            e1000_write_eeprom(hw, 0x19, 1, &eeprom_data);
            e1000_update_eeprom_checksum(hw);
        }
    }

    for (i = 0; i < (EEPROM_CHECKSUM_REG + 1); i++) {
        if (e1000_read_eeprom(hw, i, 1, &eeprom_data) < 0) {
            DEBUGOUT("EEPROM Read Error\n");
            return -E1000_ERR_EEPROM;
        }
        checksum += eeprom_data;
    }

    if (checksum == (uint16_t) EEPROM_SUM)
        return E1000_SUCCESS;
    else {
        DEBUGOUT("EEPROM Checksum Invalid\n");
        return -E1000_ERR_EEPROM;
    }
}
