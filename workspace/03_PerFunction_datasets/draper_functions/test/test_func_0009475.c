parse_edp(struct drm_i915_private *dev_priv, const struct bdb_header *bdb)
{
	const struct bdb_edp *edp;
	const struct edp_power_seq *edp_pps;
	const struct edp_link_params *edp_link_params;

	edp = find_section(bdb, BDB_EDP);
	if (!edp) {
		if (dev_priv->vbt.edp_support)
			DRM_DEBUG_KMS("No eDP BDB found but eDP panel supported.\n");
		return;
	}

	switch ((edp->color_depth >> (panel_type * 2)) & 3) {
	case EDP_18BPP:
		dev_priv->vbt.edp_bpp = 18;
		break;
	case EDP_24BPP:
		dev_priv->vbt.edp_bpp = 24;
		break;
	case EDP_30BPP:
		dev_priv->vbt.edp_bpp = 30;
		break;
	}


	edp_pps = &edp->power_seqs[panel_type];
	edp_link_params = &edp->link_params[panel_type];

	dev_priv->vbt.edp_pps = *edp_pps;

	switch (edp_link_params->rate) {
	case EDP_RATE_1_62:
		dev_priv->vbt.edp_rate = DP_LINK_BW_1_62;
		break;
	case EDP_RATE_2_7:
		dev_priv->vbt.edp_rate = DP_LINK_BW_2_7;
		break;
	default:
		DRM_DEBUG_KMS("VBT has unknown eDP link rate value %u\n",
			      edp_link_params->rate);
		break;
	}

	switch (edp_link_params->lanes) {
	case EDP_LANE_1:
		dev_priv->vbt.edp_lanes = 1;
		break;
	case EDP_LANE_2:
		dev_priv->vbt.edp_lanes = 2;
		break;
	case EDP_LANE_4:
		dev_priv->vbt.edp_lanes = 4;
		break;
	default:
		DRM_DEBUG_KMS("VBT has unknown eDP lane count value %u\n",
			      edp_link_params->lanes);
		break;
	}

	switch (edp_link_params->preemphasis) {
	case EDP_PREEMPHASIS_NONE:
		dev_priv->vbt.edp_preemphasis = DP_TRAIN_PRE_EMPH_LEVEL_0;
		break;
	case EDP_PREEMPHASIS_3_5dB:
		dev_priv->vbt.edp_preemphasis = DP_TRAIN_PRE_EMPH_LEVEL_1;
		break;
	case EDP_PREEMPHASIS_6dB:
		dev_priv->vbt.edp_preemphasis = DP_TRAIN_PRE_EMPH_LEVEL_2;
		break;
	case EDP_PREEMPHASIS_9_5dB:
		dev_priv->vbt.edp_preemphasis = DP_TRAIN_PRE_EMPH_LEVEL_3;
		break;
	default:
		DRM_DEBUG_KMS("VBT has unknown eDP pre-emphasis value %u\n",
			      edp_link_params->preemphasis);
		break;
	}

	switch (edp_link_params->vswing) {
	case EDP_VSWING_0_4V:
		dev_priv->vbt.edp_vswing = DP_TRAIN_VOLTAGE_SWING_LEVEL_0;
		break;
	case EDP_VSWING_0_6V:
		dev_priv->vbt.edp_vswing = DP_TRAIN_VOLTAGE_SWING_LEVEL_1;
		break;
	case EDP_VSWING_0_8V:
		dev_priv->vbt.edp_vswing = DP_TRAIN_VOLTAGE_SWING_LEVEL_2;
		break;
	case EDP_VSWING_1_2V:
		dev_priv->vbt.edp_vswing = DP_TRAIN_VOLTAGE_SWING_LEVEL_3;
		break;
	default:
		DRM_DEBUG_KMS("VBT has unknown eDP voltage swing value %u\n",
			      edp_link_params->vswing);
		break;
	}

	if (bdb->version >= 173) {
		uint8_t vswing;


		if (i915.edp_vswing) {
			dev_priv->edp_low_vswing = i915.edp_vswing == 1;
		} else {
			vswing = (edp->edp_vswing_preemph >> (panel_type * 4)) & 0xF;
			dev_priv->edp_low_vswing = vswing == 0;
		}
	}
}
