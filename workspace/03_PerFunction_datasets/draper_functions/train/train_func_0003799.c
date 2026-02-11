ast_channel_make_compatible_helper(struct ast_channel *from, struct ast_channel *to)
{
	struct ast_format_cap *src_cap = ast_channel_nativeformats(from);
	struct ast_format_cap *dst_cap = ast_channel_nativeformats(to);
	struct ast_format best_src_fmt;
	struct ast_format best_dst_fmt;
	int use_slin;


	if (ast_channel_tech(from)->bridge && ast_channel_tech(from)->bridge == ast_channel_tech(to)->bridge &&
	    !ast_channel_setoption(from, AST_OPTION_MAKE_COMPATIBLE, to, sizeof(struct ast_channel *), 0)) {
		return 0;
	}

	if ((ast_format_cmp(ast_channel_readformat(from), ast_channel_writeformat(to)) != AST_FORMAT_CMP_NOT_EQUAL) &&
		(ast_format_cmp(ast_channel_readformat(to), ast_channel_writeformat(from)) != AST_FORMAT_CMP_NOT_EQUAL)) {

		return 0;
	}


	if (!ast_format_cap_has_type(src_cap, AST_FORMAT_TYPE_AUDIO) || !ast_format_cap_has_type(dst_cap, AST_FORMAT_TYPE_AUDIO))
		return 0;

	if (ast_translator_best_choice(dst_cap, src_cap, &best_src_fmt, &best_dst_fmt) < 0) {
		ast_log(LOG_WARNING, "No path to translate from %s to %s\n", ast_channel_name(from), ast_channel_name(to));
		return -1;
	}


	use_slin = ast_format_is_slinear(&best_src_fmt) || ast_format_is_slinear(&best_dst_fmt) ? 1 : 0;
	if ((ast_format_cmp(&best_src_fmt, &best_dst_fmt) == AST_FORMAT_CMP_NOT_EQUAL) &&
		(ast_opt_generic_plc || ast_opt_transcode_via_slin) &&
	    (ast_translate_path_steps(&best_dst_fmt, &best_src_fmt) != 1 || use_slin)) {

		int best_sample_rate = ast_format_rate(&best_src_fmt) > ast_format_rate(&best_dst_fmt) ?
			ast_format_rate(&best_src_fmt) : ast_format_rate(&best_dst_fmt);


		ast_format_set(&best_dst_fmt, ast_format_slin_by_rate(best_sample_rate), 0);
	}

	if (ast_set_read_format(from, &best_dst_fmt) < 0) {
		ast_log(LOG_WARNING, "Unable to set read format on channel %s to %s\n", ast_channel_name(from), ast_getformatname(&best_dst_fmt));
		return -1;
	}
	if (ast_set_write_format(to, &best_dst_fmt) < 0) {
		ast_log(LOG_WARNING, "Unable to set write format on channel %s to %s\n", ast_channel_name(to), ast_getformatname(&best_dst_fmt));
		return -1;
	}
	return 0;
}
