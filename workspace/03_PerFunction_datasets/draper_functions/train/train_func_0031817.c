parser_cxx_assist_parse_expression (ParserCxxAssist* assist, IAnjutaIterable* iter, IAnjutaIterable** start_iter)
{
	IAnjutaEditor* editor = IANJUTA_EDITOR (assist->priv->iassist);
	IAnjutaIterable* res = NULL;
	IAnjutaIterable* cur_pos = ianjuta_iterable_clone (iter, NULL);
	gboolean op_start = FALSE;
	gboolean ref_start = FALSE;
	gchar* stmt = NULL;


	ianjuta_iterable_previous (cur_pos, NULL);


	do
	{
		gchar ch = ianjuta_editor_cell_get_char (IANJUTA_EDITOR_CELL(cur_pos),
		                                         0, NULL);

		if (parser_cxx_assist_is_expression_separator(ch, FALSE, iter)) {
			break;
		}

		if (ch == '.' || (op_start && ch == '-') || (ref_start && ch == ':'))
		{

			IAnjutaIterable* pre_word_start = ianjuta_iterable_clone (cur_pos,
			                                                          NULL);
			IAnjutaIterable* pre_word_end = ianjuta_iterable_clone (iter, NULL);
			IAnjutaIterable* stmt_end = ianjuta_iterable_clone (pre_word_start,
			                                                    NULL);


			ianjuta_iterable_next (stmt_end, NULL);
			if (op_start == TRUE || ref_start == TRUE)
				ianjuta_iterable_next (stmt_end, NULL);


			ianjuta_iterable_next (pre_word_start, NULL);

			if (op_start)
			{
				ianjuta_iterable_next (pre_word_start, NULL);
			}

			parser_cxx_assist_update_pre_word (assist, ianjuta_editor_get_text (
			                                                   editor,
			                                                   pre_word_start,
			                                                   pre_word_end,
			                                                   NULL));


			while (ianjuta_iterable_previous (cur_pos, NULL))
			{
				gchar word_ch = ianjuta_editor_cell_get_char (
				                        IANJUTA_EDITOR_CELL(cur_pos), 0, NULL);

				if (parser_cxx_assist_is_expression_separator(word_ch, FALSE,
				                                              cur_pos))
					break;
			}
			ianjuta_iterable_next (cur_pos, NULL);
			stmt = ianjuta_editor_get_text (editor,
			                                cur_pos, stmt_end, NULL);
			*start_iter = pre_word_start;
			g_object_unref (stmt_end);
			g_object_unref (pre_word_end);
			break;
		}
		else if (ch == '>')
			op_start = TRUE;
		else if (ch == ':')
			ref_start = TRUE;
		else
		{
			op_start = FALSE;
			ref_start = FALSE;
		}
	}
	while (ianjuta_iterable_previous (cur_pos, NULL));

	if (stmt)
	{
		gint lineno;
		gchar *above_text;
		IAnjutaIterable* start;

		if (!assist->priv->editor_filename)
		{
			g_free (stmt);
			return NULL;
		}

		start = ianjuta_editor_get_start_position (editor, NULL);
		above_text = ianjuta_editor_get_text (editor, start, iter, NULL);
		g_object_unref (start);

		lineno = ianjuta_editor_get_lineno (editor, NULL);


		res = engine_parser_process_expression (stmt,
		                                        above_text,
		                                        assist->priv->editor_filename,
		                                        lineno);
		g_free (stmt);
	}
	g_object_unref (cur_pos);
	return res;
}
