anjuta_bookmarks_session_save (AnjutaBookmarks* bookmarks, AnjutaSession* session)
{
	LIBXML_TEST_VERSION;
	int rc;
	xmlTextWriterPtr writer;
	xmlBufferPtr buf;
	GtkTreeIter iter;

	AnjutaBookmarksPrivate* priv = BOOKMARKS_GET_PRIVATE(bookmarks);


	buf = xmlBufferCreate();
	if (buf == NULL)
	{
		DEBUG_PRINT ("%s", "XmlwriterMemory: Error creating the xml buffer\n");
		return;
	}


	writer = xmlNewTextWriterMemory(buf, 0);
	if (writer == NULL)
	{
		DEBUG_PRINT ("%s", "XmlwriterMemory: Error creating the xml writer\n");
		return;
	}

	rc = xmlTextWriterStartDocument(writer, NULL, ENCODING, NULL);
	if (rc < 0) {
		DEBUG_PRINT ("%s",
					 "XmlwriterMemory: Error at xmlTextWriterStartDocument\n");
					 return;
	}
    rc = xmlTextWriterStartElement(writer, BAD_CAST "bookmarks");
    if (rc < 0) {
        DEBUG_PRINT ("%s",
            "XmlwriterMemory: Error at xmlTextWriterStartElement\n");
        return;
    }

	if (gtk_tree_model_get_iter_first (priv->model,
									   &iter))
	{
		do
		{
			gchar* title;
			GFile* file;
			gint line;
			gchar* line_text;
			gchar* uri;

			gtk_tree_model_get (priv->model,
								&iter,
								COLUMN_TEXT, &title,
								COLUMN_FILE, &file,
								COLUMN_LINE, &line,
								-1);
			uri = g_file_get_uri (file);
			g_object_unref (file);

			rc = xmlTextWriterStartElement(writer, BAD_CAST "bookmark");
			if (rc < 0) {
				DEBUG_PRINT ("%s",
					"XmlwriterMemory: Error at xmlTextWriterStartElement\n");
				return;
			}
			rc = xmlTextWriterWriteAttribute(writer, BAD_CAST "title",
											 BAD_CAST title);
			g_free (title);
			if (rc < 0) {
				DEBUG_PRINT ("%s",
					"XmlwriterMemory: Error at xmlTextWriterWriteAttribute\n");
				return;
			}
			rc = xmlTextWriterWriteAttribute(writer, BAD_CAST "uri",
											 BAD_CAST uri);
			g_free (uri);
			if (rc < 0) {
				DEBUG_PRINT ("%s",
					"XmlwriterMemory: Error at xmlTextWriterWriteAttribute\n");
				return;
			}
			line_text = g_strdup_printf ("%d", line);
			rc = xmlTextWriterWriteAttribute(writer, BAD_CAST "line",
											 BAD_CAST line_text);
			g_free (line_text);
			if (rc < 0) {
				DEBUG_PRINT ("%s",
					"XmlwriterMemory: Error at xmlTextWriterWriteAttribute\n");
				return;
			}

			rc = xmlTextWriterEndElement(writer);
			if (rc < 0) {
				DEBUG_PRINT ("%s", "XmlwriterMemory: Error at xmlTextWriterEndElement\n");
				return;
			}
		}
		while (gtk_tree_model_iter_next (priv->model, &iter));
	}
	rc = xmlTextWriterEndDocument(writer);
	if (rc < 0) {
		DEBUG_PRINT ("%s", "testXmlwriterMemory: Error at xmlTextWriterEndDocument\n");
		return;
	}
	xmlFreeTextWriter(writer);

	anjuta_session_set_string (session,
							   "Document Manager",
							   "bookmarks",
							   (const gchar*) buf->content);
	xmlBufferFree(buf);


	gtk_list_store_clear (GTK_LIST_STORE (priv->model));

	if (priv->query_scope)
	{
		g_object_unref (priv->query_scope);
		priv->query_scope = NULL;
	}
}
