build_dialplan_useage_ramp(const char *exten, int exclusive)
{
	struct parking_dp_ramp *ramp_node;

	ramp_node = ast_calloc(1, sizeof(*ramp_node) + strlen(exten));
	if (!ramp_node) {
		return NULL;
	}
	ramp_node->exclusive = exclusive;
	strcpy(ramp_node->exten, exten);
	return ramp_node;
}
