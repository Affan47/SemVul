e1000_set_phy_type(struct e1000_hw *hw)
{
    DEBUGFUNC("e1000_set_phy_type");

    if (hw->mac_type == e1000_undefined)
        return -E1000_ERR_PHY_TYPE;

    switch (hw->phy_id) {
    case M88E1000_E_PHY_ID:
    case M88E1000_I_PHY_ID:
    case M88E1011_I_PHY_ID:
    case M88E1111_I_PHY_ID:
        hw->phy_type = e1000_phy_m88;
        break;
    case IGP01E1000_I_PHY_ID:
        if (hw->mac_type == e1000_82541 ||
            hw->mac_type == e1000_82541_rev_2 ||
            hw->mac_type == e1000_82547 ||
            hw->mac_type == e1000_82547_rev_2) {
            hw->phy_type = e1000_phy_igp;
            break;
        }
    case IGP03E1000_E_PHY_ID:
        hw->phy_type = e1000_phy_igp_3;
        break;
    case IFE_E_PHY_ID:
    case IFE_PLUS_E_PHY_ID:
    case IFE_C_E_PHY_ID:
        hw->phy_type = e1000_phy_ife;
        break;
    case GG82563_E_PHY_ID:
        if (hw->mac_type == e1000_80003es2lan) {
            hw->phy_type = e1000_phy_gg82563;
            break;
        }

    default:

        hw->phy_type = e1000_phy_undefined;
        return -E1000_ERR_PHY_TYPE;
    }

    return E1000_SUCCESS;
}
