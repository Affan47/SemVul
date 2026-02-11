radeon_dp_link_train_finish(struct radeon_dp_link_train_info *dp_info)
{
	udelay(400);


	drm_dp_dpcd_writeb(dp_info->aux,
			   DP_TRAINING_PATTERN_SET,
			   DP_TRAINING_PATTERN_DISABLE);


	if (ASIC_IS_DCE4(dp_info->rdev) || !dp_info->use_dpencoder)
		atombios_dig_encoder_setup(dp_info->encoder,
					   ATOM_ENCODER_CMD_DP_LINK_TRAINING_COMPLETE, 0);
	else
		radeon_dp_encoder_service(dp_info->rdev, ATOM_DP_ACTION_TRAINING_COMPLETE,
					  dp_info->dp_clock, dp_info->enc_id, 0);

	return 0;
}
