intel_sdvo_set_value(struct intel_sdvo *intel_sdvo, u8 cmd, const void *data, int len)
{
	if (!intel_sdvo_write_cmd(intel_sdvo, cmd, data, len))
		return false;

	return intel_sdvo_read_response(intel_sdvo, NULL, 0);
}
