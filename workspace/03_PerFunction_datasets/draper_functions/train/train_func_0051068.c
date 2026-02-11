e1000_detect_gig_phy(struct e1000_hw *hw)
{
    int32_t phy_init_status, ret_val;
    uint16_t phy_id_high, phy_id_low;
    boolean_t match = FALSE;

    DEBUGFUNC("e1000_detect_gig_phy");

    if (hw->phy_id != 0)
        return E1000_SUCCESS;


    if (hw->mac_type == e1000_82571 ||
        hw->mac_type == e1000_82572) {
        hw->phy_id = IGP01E1000_I_PHY_ID;
        hw->phy_type = e1000_phy_igp_2;
        return E1000_SUCCESS;
    }


    if (hw->mac_type == e1000_80003es2lan)
        hw->phy_type = e1000_phy_gg82563;


    ret_val = e1000_read_phy_reg(hw, PHY_ID1, &phy_id_high);
    if (ret_val)
        return ret_val;

    hw->phy_id = (uint32_t) (phy_id_high << 16);
    udelay(20);
    ret_val = e1000_read_phy_reg(hw, PHY_ID2, &phy_id_low);
    if (ret_val)
        return ret_val;

    hw->phy_id |= (uint32_t) (phy_id_low & PHY_REVISION_MASK);
    hw->phy_revision = (uint32_t) phy_id_low & ~PHY_REVISION_MASK;

    switch (hw->mac_type) {
    case e1000_82543:
        if (hw->phy_id == M88E1000_E_PHY_ID) match = TRUE;
        break;
    case e1000_82544:
        if (hw->phy_id == M88E1000_I_PHY_ID) match = TRUE;
        break;
    case e1000_82540:
    case e1000_82545:
    case e1000_82545_rev_3:
    case e1000_82546:
    case e1000_82546_rev_3:
        if (hw->phy_id == M88E1011_I_PHY_ID) match = TRUE;
        break;
    case e1000_82541:
    case e1000_82541_rev_2:
    case e1000_82547:
    case e1000_82547_rev_2:
        if (hw->phy_id == IGP01E1000_I_PHY_ID) match = TRUE;
        break;
    case e1000_82573:
        if (hw->phy_id == M88E1111_I_PHY_ID) match = TRUE;
        break;
    case e1000_80003es2lan:
        if (hw->phy_id == GG82563_E_PHY_ID) match = TRUE;
        break;
    case e1000_ich8lan:
        if (hw->phy_id == IGP03E1000_E_PHY_ID) match = TRUE;
        if (hw->phy_id == IFE_E_PHY_ID) match = TRUE;
        if (hw->phy_id == IFE_PLUS_E_PHY_ID) match = TRUE;
        if (hw->phy_id == IFE_C_E_PHY_ID) match = TRUE;
        break;
    case e1000_82576:
        match = TRUE;
        break;
    default:
        DEBUGOUT1("Invalid MAC type %d\n", hw->mac_type);
        return -E1000_ERR_CONFIG;
    }
    phy_init_status = e1000_set_phy_type(hw);

    if ((match) && (phy_init_status == E1000_SUCCESS)) {
        DEBUGOUT1("PHY ID %#08x detected\n", hw->phy_id);
        return E1000_SUCCESS;
    }
    DEBUGOUT1("Invalid PHY ID %#08x\n", hw->phy_id);
    return -E1000_ERR_PHY;
}
