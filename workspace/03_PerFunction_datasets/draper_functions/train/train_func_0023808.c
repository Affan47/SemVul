e1000e_get_phy_type_from_id(u32 phy_id)
{
	enum e1000_phy_type phy_type = e1000_phy_unknown;

	switch (phy_id)	{
	case M88E1000_I_PHY_ID:
	case M88E1000_E_PHY_ID:
	case M88E1111_I_PHY_ID:
	case M88E1011_I_PHY_ID:
		phy_type = e1000_phy_m88;
		break;
	case IGP01E1000_I_PHY_ID:
		phy_type = e1000_phy_igp_2;
		break;
	case GG82563_E_PHY_ID:
		phy_type = e1000_phy_gg82563;
		break;
	case IGP03E1000_E_PHY_ID:
		phy_type = e1000_phy_igp_3;
		break;
	case IFE_E_PHY_ID:
	case IFE_PLUS_E_PHY_ID:
	case IFE_C_E_PHY_ID:
		phy_type = e1000_phy_ife;
		break;
	case BME1000_E_PHY_ID:
	case BME1000_E_PHY_ID_R2:
		phy_type = e1000_phy_bm;
		break;
	case I82578_E_PHY_ID:
		phy_type = e1000_phy_82578;
		break;
	case I82577_E_PHY_ID:
		phy_type = e1000_phy_82577;
		break;
	default:
		phy_type = e1000_phy_unknown;
		break;
	}
	return phy_type;
}
