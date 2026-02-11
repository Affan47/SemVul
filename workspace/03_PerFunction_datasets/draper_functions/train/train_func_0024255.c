intel_dp_set_edid(struct intel_dp *intel_dp)
{
	struct intel_connector *intel_connector = intel_dp->attached_connector;
	struct edid *edid;

	intel_dp_unset_edid(intel_dp);
	edid = intel_dp_get_edid(intel_dp);
	intel_connector->detect_edid = edid;

	if (intel_dp->force_audio != HDMI_AUDIO_AUTO)
		intel_dp->has_audio = intel_dp->force_audio == HDMI_AUDIO_ON;
	else
		intel_dp->has_audio = drm_detect_monitor_audio(edid);
}
