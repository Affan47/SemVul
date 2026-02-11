e_text_delete_selection (EText *text)
{
	gint sel_start, sel_end;

	sel_start = MIN (text->selection_start, text->selection_end);
	sel_end   = MAX (text->selection_start, text->selection_end);

	if (sel_start != sel_end)
		e_text_model_delete (text->model, sel_start, sel_end - sel_start);
	text->need_im_reset = TRUE;
}
