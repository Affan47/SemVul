fc_rrq_rsp_parse(struct fchs_s *fchs, int len)
{
	struct fc_els_cmd_s *els_cmd = (struct fc_els_cmd_s *) (fchs + 1);

	len = len;
	if (els_cmd->els_code != FC_ELS_ACC)
		return FC_PARSE_FAILURE;

	return FC_PARSE_OK;
}
