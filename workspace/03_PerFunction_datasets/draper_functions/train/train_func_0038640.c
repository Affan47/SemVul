evergreen_is_dp_sst_stream_enabled(struct radeon_device *rdev,
					       unsigned crtc_id, unsigned *ret_dig_fe)
{
	unsigned i;
	unsigned dig_fe;
	unsigned dig_be;
	unsigned dig_en_be;
	unsigned uniphy_pll;
	unsigned digs_fe_selected;
	unsigned dig_be_mode;
	unsigned dig_fe_mask;
	bool is_enabled = false;
	bool found_crtc = false;


	for (i = 0; i < ARRAY_SIZE(ni_dig_offsets); i++) {
		dig_fe = RREG32(NI_DIG_FE_CNTL + ni_dig_offsets[i]);
		if (dig_fe & NI_DIG_FE_CNTL_SYMCLK_FE_ON &&
		    crtc_id == NI_DIG_FE_CNTL_SOURCE_SELECT(dig_fe)) {

			found_crtc = true;
			dig_fe_mask = 1 << i;
			dig_fe = i;
			break;
		}
	}

	if (found_crtc) {

		for (i = 0; i < ARRAY_SIZE(ni_dig_offsets); i++) {
			dig_be = RREG32(NI_DIG_BE_CNTL + ni_dig_offsets[i]);

			digs_fe_selected = NI_DIG_BE_CNTL_FE_SOURCE_SELECT(dig_be);
			dig_be_mode = NI_DIG_FE_CNTL_MODE(dig_be);
			if (dig_fe_mask &  digs_fe_selected &&

			    dig_be_mode == NI_DIG_BE_DPSST) {
				dig_en_be = RREG32(NI_DIG_BE_EN_CNTL +
						   ni_dig_offsets[i]);
				uniphy_pll = RREG32(NI_DCIO_UNIPHY0_PLL_CONTROL1 +
						    ni_tx_offsets[i]);

				if (dig_en_be & NI_DIG_BE_EN_CNTL_ENABLE &&
				    dig_en_be & NI_DIG_BE_EN_CNTL_SYMBCLK_ON &&
				    uniphy_pll & NI_DCIO_UNIPHY0_PLL_CONTROL1_ENABLE) {
					is_enabled = true;
					*ret_dig_fe = dig_fe;
					break;
				}
			}
		}
	}

	return is_enabled;
}
