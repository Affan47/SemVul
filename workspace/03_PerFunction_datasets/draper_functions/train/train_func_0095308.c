e1000_adjust_serdes_amplitude(struct e1000_hw *hw)
{
    uint16_t eeprom_data;
    int32_t  ret_val;

    DEBUGFUNC("e1000_adjust_serdes_amplitude");

    if (hw->media_type != e1000_media_type_internal_serdes)
        return E1000_SUCCESS;

    switch (hw->mac_type) {
    case e1000_82545_rev_3:
    case e1000_82546_rev_3:
        break;
    default:
        return E1000_SUCCESS;
    }

    ret_val = e1000_read_eeprom(hw, EEPROM_SERDES_AMPLITUDE, 1, &eeprom_data);
    if (ret_val) {
        return ret_val;
    }

    if (eeprom_data != EEPROM_RESERVED_WORD) {

        eeprom_data &= EEPROM_SERDES_AMPLITUDE_MASK;
        ret_val = e1000_write_phy_reg(hw, M88E1000_PHY_EXT_CTRL, eeprom_data);
        if (ret_val)
            return ret_val;
    }

    return E1000_SUCCESS;
}
