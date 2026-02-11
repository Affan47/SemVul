bnxt_fw_to_ethtool_advertised_spds(struct bnxt_link_info *link_info)
{
	u16 fw_speeds = link_info->auto_link_speeds;
	u32 speed_mask = 0;


	if (fw_speeds & BNXT_LINK_SPEED_MSK_100MB)
		speed_mask |= ADVERTISED_100baseT_Full;
	if (fw_speeds & BNXT_LINK_SPEED_MSK_1GB)
		speed_mask |= ADVERTISED_1000baseT_Full;
	if (fw_speeds & BNXT_LINK_SPEED_MSK_2_5GB)
		speed_mask |= ADVERTISED_2500baseX_Full;
	if (fw_speeds & BNXT_LINK_SPEED_MSK_10GB)
		speed_mask |= ADVERTISED_10000baseT_Full;

	if (fw_speeds & BNXT_LINK_SPEED_MSK_20GB)
		speed_mask |= ADVERTISED_20000baseMLD2_Full |
			      ADVERTISED_20000baseKR2_Full;
	if (fw_speeds & BNXT_LINK_SPEED_MSK_40GB)
		speed_mask |= ADVERTISED_40000baseKR4_Full |
			      ADVERTISED_40000baseCR4_Full |
			      ADVERTISED_40000baseSR4_Full |
			      ADVERTISED_40000baseLR4_Full;
	return speed_mask;
}
