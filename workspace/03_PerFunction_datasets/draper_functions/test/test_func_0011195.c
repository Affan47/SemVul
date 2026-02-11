set_speed_mask(u8 *speed_mask, struct asd_phy_desc *pd)
{

	*speed_mask = SAS_SPEED_60_DIS | SAS_SPEED_30_DIS | SAS_SPEED_15_DIS
		| SATA_SPEED_30_DIS | SATA_SPEED_15_DIS;

	switch (pd->max_sas_lrate) {
	case SAS_LINK_RATE_6_0_GBPS:
		*speed_mask &= ~SAS_SPEED_60_DIS;
	default:
	case SAS_LINK_RATE_3_0_GBPS:
		*speed_mask &= ~SAS_SPEED_30_DIS;
	case SAS_LINK_RATE_1_5_GBPS:
		*speed_mask &= ~SAS_SPEED_15_DIS;
	}

	switch (pd->min_sas_lrate) {
	case SAS_LINK_RATE_6_0_GBPS:
		*speed_mask |= SAS_SPEED_30_DIS;
	case SAS_LINK_RATE_3_0_GBPS:
		*speed_mask |= SAS_SPEED_15_DIS;
	default:
	case SAS_LINK_RATE_1_5_GBPS:

		;
	}

	switch (pd->max_sata_lrate) {
	case SAS_LINK_RATE_3_0_GBPS:
		*speed_mask &= ~SATA_SPEED_30_DIS;
	default:
	case SAS_LINK_RATE_1_5_GBPS:
		*speed_mask &= ~SATA_SPEED_15_DIS;
	}

	switch (pd->min_sata_lrate) {
	case SAS_LINK_RATE_3_0_GBPS:
		*speed_mask |= SATA_SPEED_15_DIS;
	default:
	case SAS_LINK_RATE_1_5_GBPS:

		;
	}
}
