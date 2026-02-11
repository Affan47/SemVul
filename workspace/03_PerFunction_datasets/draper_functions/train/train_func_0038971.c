intel_dp_handle_test_request(struct intel_dp *intel_dp)
{
	uint8_t response = DP_TEST_NAK;
	uint8_t rxdata = 0;
	int status = 0;

	intel_dp->compliance_test_active = 0;
	intel_dp->compliance_test_type = 0;
	intel_dp->compliance_test_data = 0;

	intel_dp->aux.i2c_nack_count = 0;
	intel_dp->aux.i2c_defer_count = 0;

	status = drm_dp_dpcd_read(&intel_dp->aux, DP_TEST_REQUEST, &rxdata, 1);
	if (status <= 0) {
		DRM_DEBUG_KMS("Could not read test request from sink\n");
		goto update_status;
	}

	switch (rxdata) {
	case DP_TEST_LINK_TRAINING:
		DRM_DEBUG_KMS("LINK_TRAINING test requested\n");
		intel_dp->compliance_test_type = DP_TEST_LINK_TRAINING;
		response = intel_dp_autotest_link_training(intel_dp);
		break;
	case DP_TEST_LINK_VIDEO_PATTERN:
		DRM_DEBUG_KMS("TEST_PATTERN test requested\n");
		intel_dp->compliance_test_type = DP_TEST_LINK_VIDEO_PATTERN;
		response = intel_dp_autotest_video_pattern(intel_dp);
		break;
	case DP_TEST_LINK_EDID_READ:
		DRM_DEBUG_KMS("EDID test requested\n");
		intel_dp->compliance_test_type = DP_TEST_LINK_EDID_READ;
		response = intel_dp_autotest_edid(intel_dp);
		break;
	case DP_TEST_LINK_PHY_TEST_PATTERN:
		DRM_DEBUG_KMS("PHY_PATTERN test requested\n");
		intel_dp->compliance_test_type = DP_TEST_LINK_PHY_TEST_PATTERN;
		response = intel_dp_autotest_phy_pattern(intel_dp);
		break;
	default:
		DRM_DEBUG_KMS("Invalid test request '%02x'\n", rxdata);
		break;
	}

update_status:
	status = drm_dp_dpcd_write(&intel_dp->aux,
				   DP_TEST_RESPONSE,
				   &response, 1);
	if (status <= 0)
		DRM_DEBUG_KMS("Could not write test response to sink\n");
}
