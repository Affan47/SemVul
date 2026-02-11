force_rport_string(struct ast_flags *flags)
{
	if (ast_test_flag(&flags[2], SIP_PAGE3_NAT_AUTO_RPORT)) {
		return ast_test_flag(&flags[0], SIP_NAT_FORCE_RPORT) ? "Auto (Yes)" : "Auto (No)";
	}
	return AST_CLI_YESNO(ast_test_flag(&flags[0], SIP_NAT_FORCE_RPORT));
}
