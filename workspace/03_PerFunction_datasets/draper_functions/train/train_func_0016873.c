pgd_forms_get_form_fields (GtkWidget    *button,
			   PgdFormsDemo *demo)
{
	PopplerPage *page;
	GList       *mapping, *l;
	gint         n_fields;
	GTimer      *timer;

	gtk_list_store_clear (demo->model);
	pgd_form_field_view_set_field (demo->field_view, NULL);

	page = poppler_document_get_page (demo->doc, demo->page);
	if (!page)
		return;

	timer = g_timer_new ();
	mapping = poppler_page_get_form_field_mapping (page);
	g_timer_stop (timer);

	n_fields = g_list_length (mapping);
	if (n_fields > 0) {
		gchar *str;

		str = g_strdup_printf ("<i>%d form fields found in %.4f seconds</i>",
				       n_fields, g_timer_elapsed (timer, NULL));
		gtk_label_set_markup (GTK_LABEL (demo->timer_label), str);
		g_free (str);
	} else {
		gtk_label_set_markup (GTK_LABEL (demo->timer_label), "<i>No form fields found</i>");
	}

	g_timer_destroy (timer);

	for (l = mapping; l; l = g_list_next (l)) {
		PopplerFormFieldMapping *fmapping;
		GtkTreeIter              iter;
		gchar                   *x1, *y1, *x2, *y2;

		fmapping = (PopplerFormFieldMapping *)l->data;

		x1 = g_strdup_printf ("%.2f", fmapping->area.x1);
		y1 = g_strdup_printf ("%.2f", fmapping->area.y1);
		x2 = g_strdup_printf ("%.2f", fmapping->area.x2);
		y2 = g_strdup_printf ("%.2f", fmapping->area.y2);

		gtk_list_store_append (demo->model, &iter);
		gtk_list_store_set (demo->model, &iter,
				    FORMS_FIELD_TYPE_COLUMN, get_form_field_type (fmapping->field),
				    FORMS_ID_COLUMN, poppler_form_field_get_id (fmapping->field),
				    FORMS_READ_ONLY_COLUMN, poppler_form_field_is_read_only (fmapping->field),
				    FORMS_X1_COLUMN, x1,
				    FORMS_Y1_COLUMN, y1,
				    FORMS_X2_COLUMN, x2,
				    FORMS_Y2_COLUMN, y2,
				    FORMS_FIELD_COLUMN, fmapping->field,
				    -1);
		g_free (x1);
		g_free (y1);
		g_free (x2);
		g_free (y2);
	}

	poppler_page_free_form_field_mapping (mapping);
	g_object_unref (page);
}
