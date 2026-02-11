e1000_check_polarity(struct e1000_hw *hw,
                     e1000_rev_polarity *polarity)
{
    int32_t ret_val;
    uint16_t phy_data;

    DEBUGFUNC("e1000_check_polarity");

    if ((hw->phy_type == e1000_phy_m88) ||
        (hw->phy_type == e1000_phy_gg82563)) {

        ret_val = e1000_read_phy_reg(hw, M88E1000_PHY_SPEC_STATUS,
                                     &phy_data);
        if (ret_val)
            return ret_val;
        *polarity = ((phy_data & M88E1000_PSSR_REV_POLARITY) >>
                     M88E1000_PSSR_REV_POLARITY_SHIFT) ?
                     e1000_rev_polarity_reversed : e1000_rev_polarity_normal;

    } else if (hw->phy_type == e1000_phy_igp ||
              hw->phy_type == e1000_phy_igp_3 ||
              hw->phy_type == e1000_phy_igp_2) {

        ret_val = e1000_read_phy_reg(hw, IGP01E1000_PHY_PORT_STATUS,
                                     &phy_data);
        if (ret_val)
            return ret_val;


        if ((phy_data & IGP01E1000_PSSR_SPEED_MASK) ==
           IGP01E1000_PSSR_SPEED_1000MBPS) {


            ret_val = e1000_read_phy_reg(hw, IGP01E1000_PHY_PCS_INIT_REG,
                                         &phy_data);
            if (ret_val)
                return ret_val;


            *polarity = (phy_data & IGP01E1000_PHY_POLARITY_MASK) ?
                         e1000_rev_polarity_reversed : e1000_rev_polarity_normal;
        } else {


            *polarity = (phy_data & IGP01E1000_PSSR_POLARITY_REVERSED) ?
                         e1000_rev_polarity_reversed : e1000_rev_polarity_normal;
        }
    } else if (hw->phy_type == e1000_phy_ife) {
        ret_val = e1000_read_phy_reg(hw, IFE_PHY_EXTENDED_STATUS_CONTROL,
                                     &phy_data);
        if (ret_val)
            return ret_val;
        *polarity = ((phy_data & IFE_PESC_POLARITY_REVERSED) >>
                     IFE_PESC_POLARITY_REVERSED_SHIFT) ?
                     e1000_rev_polarity_reversed : e1000_rev_polarity_normal;
    }
    return E1000_SUCCESS;
}
