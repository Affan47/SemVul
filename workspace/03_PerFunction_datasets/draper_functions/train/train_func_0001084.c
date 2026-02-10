agent_write(struct ast_channel *ast, struct ast_frame *f)
{
	struct agent_pvt *p = ast_channel_tech_pvt(ast);
	int res = -1;
	CHECK_FORMATS(ast, p);
	ast_mutex_lock(&p->lock);
	if (!p->chan)
		res = 0;
	else {
		if ((f->frametype != AST_FRAME_VOICE) ||
		    (f->frametype != AST_FRAME_VIDEO) ||
		    (ast_format_cmp(&f->subclass.format, ast_channel_writeformat(p->chan)) != AST_FORMAT_CMP_NOT_EQUAL)) {
			res = ast_write(p->chan, f);
		} else {
			ast_debug(1, "Dropping one incompatible %s frame on '%s' to '%s'\n",
				f->frametype == AST_FRAME_VOICE ? "audio" : "video",
				ast_channel_name(ast), ast_channel_name(p->chan));
			res = 0;
		}
	}
	CLEANUP(ast, p);
	ast_mutex_unlock(&p->lock);
	return res;
}
