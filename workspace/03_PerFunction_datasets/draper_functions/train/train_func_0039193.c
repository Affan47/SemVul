hf_insert_hf_stock_tag (HFCustomizeState *hf_state, GtkTextBuffer *buffer,
			HFFieldType type, const char *options)
{
	GtkTextIter iter;
	gchar const *stock_id;
	GdkPixbuf* pix;
	GtkTextMark *new_mark;
	HFMarkInfo *mark_info;


	switch (type) {
	case HF_FIELD_FILE:
		stock_id = GTK_STOCK_FILE;
		break;
	case HF_FIELD_PATH:
		stock_id = GTK_STOCK_DIRECTORY;
		break;
	case HF_FIELD_PAGE:
		stock_id = "Gnumeric_Pagesetup_HF_Page";
		break;
	case HF_FIELD_PAGES:
		stock_id = "Gnumeric_Pagesetup_HF_Pages";
		break;
	case HF_FIELD_DATE:
		stock_id = "Gnumeric_Pagesetup_HF_Date";
		break;
	case HF_FIELD_TIME:
		stock_id = "Gnumeric_Pagesetup_HF_Time";
		break;
	case HF_FIELD_SHEET:
		stock_id = "Gnumeric_Pagesetup_HF_Sheet";
		break;
	case HF_FIELD_CELL:
		stock_id = "Gnumeric_Pagesetup_HF_Cell";
		break;
	default:
		return;
	}

	hf_delete_tag_cb (hf_state);

	if (gtk_text_buffer_insert_interactive_at_cursor
	    (buffer, "", -1, TRUE)) {
		gtk_text_buffer_get_iter_at_mark
			(buffer, &iter, gtk_text_buffer_get_insert (buffer));

		pix = gtk_widget_render_icon_pixbuf (GTK_WIDGET (hf_state->dialog),
					      stock_id,
					      GTK_ICON_SIZE_MENU);
		gtk_text_buffer_insert_pixbuf (buffer, &iter, pix);
		gtk_text_iter_backward_char (&iter);
		new_mark = gtk_text_buffer_create_mark (buffer, NULL,
							&iter, FALSE);
		g_object_ref (new_mark);

		mark_info = g_new0 (HFMarkInfo, 1);
		mark_info->mark = new_mark;
		mark_info->type = type;
		mark_info->options = g_strdup (options);
		hf_state->marks = g_list_append (hf_state->marks, mark_info);
	}
}
