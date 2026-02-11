ast_translate_available_formats(struct ast_format_cap *dest, struct ast_format_cap *src, struct ast_format_cap *result)
{
	struct ast_format tmp_fmt;
	struct ast_format cur_dest, cur_src;
	int src_audio = 0;
	int src_video = 0;
	int index;

	ast_format_cap_iter_start(dest);
	while (!ast_format_cap_iter_next(dest, &cur_dest)) {

		if (ast_format_cap_get_compatible_format(src, &cur_dest, &tmp_fmt)) {
			ast_format_cap_add(result, &tmp_fmt);
		} else {

			ast_format_cap_add(result, &cur_dest);
		}
	}
	ast_format_cap_iter_end(dest);


	if (!src) {
		return;
	}

	ast_format_cap_iter_start(src);
	while (!ast_format_cap_iter_next(src, &cur_src)) {

		if (AST_FORMAT_GET_TYPE(cur_src.id) == AST_FORMAT_TYPE_AUDIO) {
			src_audio = format2index(cur_src.id);
		}


		if (AST_FORMAT_GET_TYPE(cur_src.id) == AST_FORMAT_TYPE_VIDEO) {
			src_video = format2index(cur_src.id);
		}

		AST_RWLIST_RDLOCK(&translators);


		for (index = 0; (src_audio >= 0) && index < cur_max_index; index++) {
			ast_format_set(&tmp_fmt, index2format(index), 0);

			if (AST_FORMAT_GET_TYPE(tmp_fmt.id) != AST_FORMAT_TYPE_AUDIO) {
				continue;
			}


			if (!ast_format_cap_iscompatible(dest, &tmp_fmt)) {
				continue;
			}


			if (ast_format_cap_iscompatible(src, &tmp_fmt)) {
				continue;
			}


			if (!matrix_get(src_audio, index)->step) {
				ast_format_cap_remove_byid(result, tmp_fmt.id);
				continue;
			}


			if (!matrix_get(index, src_audio)->step) {
				ast_format_cap_remove_byid(result, tmp_fmt.id);
			}
		}


		for (index = 0; (src_video >= 0) && index < cur_max_index; index++) {
			ast_format_set(&tmp_fmt, index2format(index), 0);
			if (AST_FORMAT_GET_TYPE(tmp_fmt.id) != AST_FORMAT_TYPE_VIDEO) {
				continue;
			}


			if (!ast_format_cap_iscompatible(dest, &tmp_fmt)) {
				continue;
			}


			if (ast_format_cap_iscompatible(src, &tmp_fmt)) {
				continue;
			}


			if (!matrix_get(src_video, index)->step) {
				ast_format_cap_remove_byid(result, tmp_fmt.id);
				continue;
			}


			if (!matrix_get(index, src_video)->step) {
				ast_format_cap_remove_byid(result, tmp_fmt.id);
			}
		}
		AST_RWLIST_UNLOCK(&translators);
	}
	ast_format_cap_iter_end(src);
}
