pgd_text_get_text (GtkWidget   *button,
		   PgdTextDemo *demo)
{
	PopplerPage      *page;
	PopplerRectangle *recs = NULL;
	guint             n_recs;
	gchar            *text;
	GTimer           *timer;
	gint              i;

	page = poppler_document_get_page (demo->doc, demo->page);
	if (!page)
		return;

	gtk_list_store_clear (demo->model);
        if (demo->text_attrs)
                poppler_page_free_text_attributes (demo->text_attrs);
        demo->text_attrs = NULL;

	timer = g_timer_new ();
	text = poppler_page_get_text (page);
	g_timer_stop (timer);

	if (text) {
		gchar  *str;
		gdouble text_elapsed, layout_elapsed;

		text_elapsed = g_timer_elapsed (timer, NULL);

		g_timer_start (timer);
		poppler_page_get_text_layout (page, &recs, &n_recs);
		g_timer_stop (timer);

                layout_elapsed = g_timer_elapsed (timer, NULL);

                g_timer_start (timer);
                demo->text_attrs = poppler_page_get_text_attributes (page);
                g_timer_stop (timer);

		str = g_strdup_printf ("<i>got text in %.4f seconds, text layout in %.4f seconds, text attrs in %.4f seconds</i>",
				       text_elapsed, layout_elapsed, g_timer_elapsed (timer, NULL));
		gtk_label_set_markup (GTK_LABEL (demo->timer_label), str);
		g_free (str);
	} else {
		gtk_label_set_markup (GTK_LABEL (demo->timer_label), "<i>No text found</i>");
		n_recs = 0;
	}

	g_timer_destroy (timer);
	g_object_unref (page);

	if (text) {
		gtk_text_buffer_set_text (demo->buffer, text, strlen (text));
		g_free (text);
	}

	for (i = 0; i < n_recs; i++) {
		GtkTreeIter iter;
		gchar      *x1, *y1, *x2, *y2;
		gchar      *offset;

		x1 = g_strdup_printf ("%.2f", recs[i].x1);
		y1 = g_strdup_printf ("%.2f", recs[i].y1);
		x2 = g_strdup_printf ("%.2f", recs[i].x2);
		y2 = g_strdup_printf ("%.2f", recs[i].y2);

		offset = g_strdup_printf ("%d", i);

		gtk_list_store_append (demo->model, &iter);
		gtk_list_store_set (demo->model, &iter,
				    TEXT_X1_COLUMN, x1,
				    TEXT_Y1_COLUMN, y1,
				    TEXT_X2_COLUMN, x2,
				    TEXT_Y2_COLUMN, y2,
				    TEXT_OFFSET_COLUMN, offset,
				    TEXT_OFFPTR_COLUMN, GINT_TO_POINTER (i),
				    -1);

		g_free (x1);
		g_free (y1);
		g_free (x2);
		g_free (y2);
		g_free (offset);
	}

	g_free (recs);
}
