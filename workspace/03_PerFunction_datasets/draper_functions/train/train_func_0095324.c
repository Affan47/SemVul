local_digit_begin(struct ast_channel *ast, char digit)
{
	struct local_pvt *p = ast_channel_tech_pvt(ast);
	int res = -1;
	struct ast_frame f = { AST_FRAME_DTMF_BEGIN, };
	int isoutbound;

	if (!p) {
		return -1;
	}

	ao2_ref(p, 1);
	ao2_lock(p);
	isoutbound = IS_OUTBOUND(ast, p);
	f.subclass.integer = digit;
	res = local_queue_frame(p, isoutbound, &f, ast, 0);
	ao2_unlock(p);
	ao2_ref(p, -1);

	return res;
}
