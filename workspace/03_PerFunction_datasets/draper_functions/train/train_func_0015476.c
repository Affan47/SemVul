bridge_request(const char *type, struct ast_format_cap *cap, const struct ast_channel *requestor, const char *data, int *cause)
{
	struct bridge_pvt *p = NULL;
	struct ast_format slin;


	if (!(p = ao2_alloc(sizeof(*p), NULL))) {
		return NULL;
	}


	if (!(p->input = ast_channel_alloc(1, AST_STATE_UP, 0, 0, "", "", "", requestor ? ast_channel_linkedid(requestor) : NULL, 0, "Bridge/%p-input", p))) {
		ao2_ref(p, -1);
		return NULL;
	}
	if (!(p->output = ast_channel_alloc(1, AST_STATE_UP, 0, 0, "", "", "", requestor ? ast_channel_linkedid(requestor) : NULL, 0, "Bridge/%p-output", p))) {
		p->input = ast_channel_release(p->input);
		ao2_ref(p, -1);
		return NULL;
	}


	ast_channel_tech_set(p->input, &bridge_tech);
	ast_channel_tech_set(p->output, &bridge_tech);

	ao2_ref(p, 2);
	ast_channel_tech_pvt_set(p->input, p);
	ast_channel_tech_pvt_set(p->output, p);

	ast_format_set(&slin, AST_FORMAT_SLINEAR, 0);

	ast_format_cap_add(ast_channel_nativeformats(p->input), &slin);
	ast_format_cap_add(ast_channel_nativeformats(p->output), &slin);
	ast_format_copy(ast_channel_readformat(p->input), &slin);
	ast_format_copy(ast_channel_readformat(p->output), &slin);
	ast_format_copy(ast_channel_rawreadformat(p->input), &slin);
	ast_format_copy(ast_channel_rawreadformat(p->output), &slin);
	ast_format_copy(ast_channel_writeformat(p->input), &slin);
	ast_format_copy(ast_channel_writeformat(p->output), &slin);
	ast_format_copy(ast_channel_rawwriteformat(p->input), &slin);
	ast_format_copy(ast_channel_rawwriteformat(p->output), &slin);

	ast_answer(p->output);
	ast_answer(p->input);


	ao2_ref(p, -1);
	return p->input;
}
