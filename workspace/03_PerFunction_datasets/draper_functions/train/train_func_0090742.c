_e2_treedlg_response_cb (GtkDialog *dialog, gint response,
	E2_TreeDialogRuntime *rt)
{
	switch (response)
	{
		case E2_RESPONSE_USER1:
			rt->show_hidden = !rt->show_hidden;
			_e2_treedlg_refresh_cb (NULL, rt);
			e2_button_set_image (rt->hiddenbtn, (rt->show_hidden) ?
				"hidden_noshow_"E2IP".png" : "hidden_show_"E2IP".png");
			break;
		default:
			gtk_widget_hide (rt->dialog);
#ifndef ENABLE_FULL_TREE
			g_hash_table_destroy (rt->dirhash);
#endif
			show_hidden = rt->show_hidden;
#ifndef STRICT_HIDE
			strict_hide = rt->strict_hide;
#endif
			window_width = rt->dialog->allocation.width;
			window_height = rt->dialog->allocation.height;
			gtk_widget_destroy (rt->dialog);
			DEALLOCATE (E2_TreeDialogRuntime, rt);
			break;
	}
}
