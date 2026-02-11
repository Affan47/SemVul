on_file_close(void)
{
	if (!check_text_modification()) {
		force_block_cb_modified_changed(pub->mw->view);

		gtk_text_buffer_set_text(pub->mw->buffer, "", 0);
		gtk_text_buffer_set_modified(pub->mw->buffer, FALSE);
		if (pub->fi->filename)
			g_free(pub->fi->filename);
		pub->fi->filename = NULL;
		if (pub->fi->charset)
			g_free(pub->fi->charset);
		pub->fi->charset = NULL;
		pub->fi->charset_flag = FALSE;
		pub->fi->lineend = LF;
		undo_clear_all(pub->mw->buffer);

		force_call_cb_modified_changed(pub->mw->view);
		force_unblock_cb_modified_changed(pub->mw->view);


	}
}
