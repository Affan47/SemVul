psb_intel_sdvo_get_trained_inputs(struct psb_intel_sdvo *psb_intel_sdvo, bool *input_1, bool *input_2)
{
	struct psb_intel_sdvo_get_trained_inputs_response response;

	BUILD_BUG_ON(sizeof(response) != 1);
	if (!psb_intel_sdvo_get_value(psb_intel_sdvo, SDVO_CMD_GET_TRAINED_INPUTS,
				  &response, sizeof(response)))
		return false;

	*input_1 = response.input0_trained;
	*input_2 = response.input1_trained;
	return true;
}
