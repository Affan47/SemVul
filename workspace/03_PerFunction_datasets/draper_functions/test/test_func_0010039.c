pan_window_message(PanWindow *pw, const gchar *text)
{
	GList *work;
	gint count = 0;
	gint64 size = 0;
	gchar *ss;
	gchar *buf;

	if (text)
		{
		gtk_label_set_text(GTK_LABEL(pw->label_message), text);
		return;
		}

	work = pw->list_static;
	if (pw->layout == PAN_LAYOUT_CALENDAR)
		{
		while (work)
			{
			PanItem *pi;

			pi = work->data;
			work = work->next;

			if (pi->fd &&
			    pi->type == PAN_ITEM_BOX &&
			    pi->key && strcmp(pi->key, "dot") == 0)
				{
				size += pi->fd->size;
				count++;
				}
			}
		}
	else
		{
		while (work)
			{
			PanItem *pi;

			pi = work->data;
			work = work->next;

			if (pi->fd &&
			    (pi->type == PAN_ITEM_THUMB || pi->type == PAN_ITEM_IMAGE))
				{
				size += pi->fd->size;
				count++;
				}
			}
		}

	ss = text_from_size_abrev(size);
	buf = g_strdup_printf(_("%d images, %s"), count, ss);
	g_free(ss);
	gtk_label_set_text(GTK_LABEL(pw->label_message), buf);
	g_free(buf);
}
