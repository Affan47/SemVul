e1000_setup_led(struct e1000_hw *hw)
{
    uint32_t ledctl;
    int32_t ret_val = E1000_SUCCESS;

    DEBUGFUNC("e1000_setup_led");

    switch (hw->mac_type) {
    case e1000_82542_rev2_0:
    case e1000_82542_rev2_1:
    case e1000_82543:
    case e1000_82544:

        break;
    case e1000_82541:
    case e1000_82547:
    case e1000_82541_rev_2:
    case e1000_82547_rev_2:

        ret_val = e1000_read_phy_reg(hw, IGP01E1000_GMII_FIFO,
                                     &hw->phy_spd_default);
        if (ret_val)
            return ret_val;
        ret_val = e1000_write_phy_reg(hw, IGP01E1000_GMII_FIFO,
                                      (uint16_t)(hw->phy_spd_default &
                                      ~IGP01E1000_GMII_SPD));
        if (ret_val)
            return ret_val;

    default:
        if (hw->media_type == e1000_media_type_fiber) {
            ledctl = E1000_READ_REG(hw, LEDCTL);

            hw->ledctl_default = ledctl;

            ledctl &= ~(E1000_LEDCTL_LED0_IVRT |
                        E1000_LEDCTL_LED0_BLINK |
                        E1000_LEDCTL_LED0_MODE_MASK);
            ledctl |= (E1000_LEDCTL_MODE_LED_OFF <<
                       E1000_LEDCTL_LED0_MODE_SHIFT);
            E1000_WRITE_REG(hw, LEDCTL, ledctl);
        } else if (hw->media_type == e1000_media_type_copper)
            E1000_WRITE_REG(hw, LEDCTL, hw->ledctl_mode1);
        break;
    }

    return E1000_SUCCESS;
}
