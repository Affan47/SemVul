wcn36xx_detect_chip_version(struct wcn36xx *wcn)
{
	if (get_feat_caps(wcn->fw_feat_caps, DOT11AC)) {
		wcn36xx_info("Chip is 3680\n");
		wcn->chip_version = WCN36XX_CHIP_3680;
	} else {
		wcn36xx_info("Chip is 3660\n");
		wcn->chip_version = WCN36XX_CHIP_3660;
	}
}
