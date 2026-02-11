_e2_view_dialog_response_cb (GtkDialog *dialog, gint response,
	E2_ViewDialogRuntime *rt)
{
	printd (DEBUG, "_e2_view_dialog_response_cb (dialog:_,response:%d,rt:_)", response);
	switch (response)
	{
		case E2_RESPONSE_USER1:
			rt->textwrap = !rt->textwrap;
			gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (rt->textview),
				rt->textwrap ? GTK_WRAP_WORD: GTK_WRAP_NONE);
			break;
		case E2_RESPONSE_USER2:
		case E2_RESPONSE_FIND:
			if (!rt->is_hidden)
			{


				GdkModifierType mask = e2_utils_get_modifiers () &
					gtk_accelerator_get_default_mod_mask ();
				if (mask & GDK_SHIFT_MASK)
				{
					rt->search_backward = !rt->search_backward;
					e2_view_dialog_search (response == E2_RESPONSE_FIND, FALSE, rt);
					rt->search_backward = !rt->search_backward;
				}
				else

					e2_view_dialog_search (response == E2_RESPONSE_FIND, FALSE, rt);
			}
			else
			{
				gtk_widget_show (rt->panel);
				rt->is_hidden = FALSE;
				if (rt->hidebtn != NULL)
					gtk_widget_show (rt->hidebtn);

				GtkTextIter start_iter, end_iter;
				if (gtk_text_buffer_get_selection_bounds (rt->textbuffer,
						&start_iter, &end_iter))
				{
					gchar *find_string = gtk_text_buffer_get_text
						(rt->textbuffer, &start_iter, &end_iter, FALSE);
					gtk_entry_set_text (GTK_ENTRY (GTK_BIN (rt->combo)->child),
						find_string);
					gtk_editable_select_region (GTK_EDITABLE (GTK_BIN (rt->combo)->child), 0, -1);
					e2_view_dialog_search (response == E2_RESPONSE_FIND, FALSE, rt);
					g_free (find_string);
				}
				else
					e2_view_dialog_update_combo (rt->combo);


				gtk_widget_grab_focus (GTK_BIN (rt->combo)->child);

				if (rt->findbtn != NULL)
					e2_widget_swap_tooltip (rt->findbtn);
			}
			break;


		case E2_RESPONSE_USER3:
		{

			GtkWidget *entry = GTK_BIN (rt->combo)->child;
			const gchar *find = gtk_entry_get_text (GTK_ENTRY (entry));
			if (*find != '\0')
			{
				e2_combobox_activated_cb (entry, GINT_TO_POINTER (FALSE));
				e2_list_update_history (find, &find_history, NULL, 30, FALSE);
			}
			gtk_widget_hide (rt->panel);
			rt->is_hidden = TRUE;

			if (rt->hidebtn != NULL)
				gtk_widget_hide (rt->hidebtn);
			gtk_widget_hide (rt->info_label);

#ifdef E2_MARK_FINDS

			e2_view_dialog_clear_hilites (rt);
#endif

			GtkTextIter iter;
			if (gtk_text_buffer_get_selection_bounds (rt->textbuffer, &iter, NULL))
				gtk_text_buffer_select_range (rt->textbuffer, &iter, &iter);

			if (rt->findbtn != NULL)
				e2_widget_swap_tooltip (rt->findbtn);
			gtk_widget_grab_focus (rt->textview);
		}
			break;
		default:
			e2_view_dialog_destroy (rt);
			break;
	}
}
