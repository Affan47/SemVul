gl_object_editor_init (glObjectEditor *editor)
{
        gchar        *builder_filename;
        static gchar *object_ids[] = { "editor_vbox",
                                       "adjustment1",  "adjustment2",  "adjustment3",
                                       "adjustment4",  "adjustment5",  "adjustment6",
                                       "adjustment7",  "adjustment8",  "adjustment9",
                                       "adjustment10", "adjustment11", "adjustment12",
                                       "adjustment13", "page_sizegroup", "width_sizegroup",
                                       NULL };
        GError       *error = NULL;
        gchar        *s;

	gl_debug (DEBUG_EDITOR, "START");

	editor->priv = g_new0 (glObjectEditorPrivate, 1);

        editor->priv->builder = gtk_builder_new ();

        builder_filename = g_build_filename (GLABELS_DATA_DIR, "ui", "object-editor.ui", NULL);
        gtk_builder_add_objects_from_file (editor->priv->builder, builder_filename, object_ids, &error);
        g_free (builder_filename);
	if (error) {
		g_critical ("%s\n\ngLabels may not be installed correctly!", error->message);
                g_error_free (error);
		return;
	}

        gl_builder_util_get_widgets (editor->priv->builder,
                                     "editor_vbox", &editor->priv->editor_vbox,
                                     "title_image", &editor->priv->title_image,
                                     "title_label", &editor->priv->title_label,
                                     "notebook",    &editor->priv->notebook,
                                     NULL);

	gtk_box_pack_start (GTK_BOX(editor),
			    editor->priv->editor_vbox,
			    FALSE, FALSE, 0);

	gtk_widget_show_all (GTK_WIDGET(editor));

        gtk_image_set_from_icon_name (GTK_IMAGE(editor->priv->title_image),
                                      "glabels-object-properties",
                                      GTK_ICON_SIZE_LARGE_TOOLBAR);

        s = g_strdup_printf ("<span weight=\"bold\">%s</span>",
                             _("Object properties"));
        gtk_label_set_text (GTK_LABEL(editor->priv->title_label), s);
        gtk_label_set_use_markup (GTK_LABEL(editor->priv->title_label), TRUE);
        g_free (s);

        gtk_widget_set_sensitive (editor->priv->title_image, FALSE);
        gtk_widget_set_sensitive (editor->priv->title_label, FALSE);


	gtk_widget_hide (editor->priv->notebook);
	gtk_widget_set_no_show_all (editor->priv->notebook, TRUE);

	gl_debug (DEBUG_EDITOR, "END");
}
