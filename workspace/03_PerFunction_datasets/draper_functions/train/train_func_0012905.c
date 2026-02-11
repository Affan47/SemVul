ast_framehook_detach(struct ast_channel *chan, int id)
{
	struct ast_framehook *framehook;
	int res = -1;

	if (!ast_channel_framehooks(chan)) {
		return res;
	}

	AST_LIST_TRAVERSE_SAFE_BEGIN(&ast_channel_framehooks(chan)->list, framehook, list) {
		if (framehook->id == id) {


			framehook->detach_and_destroy_me = 1;
			res = 0;
			break;
		}
	}
	AST_LIST_TRAVERSE_SAFE_END;

	return res;
}
