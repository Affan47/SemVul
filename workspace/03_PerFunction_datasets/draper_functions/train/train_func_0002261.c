e1000_kumeran_lock_loss_workaround(struct e1000_hw *hw)
{
    int32_t ret_val;
    int32_t reg;
    int32_t cnt;
    uint16_t phy_data;

    if (hw->kmrn_lock_loss_workaround_disabled)
        return E1000_SUCCESS;


    ret_val = e1000_read_phy_reg(hw, PHY_STATUS, &phy_data);
    ret_val = e1000_read_phy_reg(hw, PHY_STATUS, &phy_data);

    if (phy_data & MII_SR_LINK_STATUS) {
        for (cnt = 0; cnt < 10; cnt++) {

            ret_val = e1000_read_phy_reg(hw, IGP3_KMRN_DIAG, &phy_data);
            if (ret_val)
                return ret_val;

            ret_val = e1000_read_phy_reg(hw, IGP3_KMRN_DIAG, &phy_data);
            if (ret_val)
                return ret_val;


            if (!(phy_data & IGP3_KMRN_DIAG_PCS_LOCK_LOSS))
                return E1000_SUCCESS;


            e1000_phy_hw_reset(hw);
            mdelay(5);
        }

        reg = E1000_READ_REG(hw, PHY_CTRL);
        E1000_WRITE_REG(hw, PHY_CTRL, reg | E1000_PHY_CTRL_GBE_DISABLE |
                        E1000_PHY_CTRL_NOND0A_GBE_DISABLE);


        return E1000_ERR_PHY;
    }

    return E1000_SUCCESS;
}
