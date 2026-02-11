_document_loader_load_file_finish (GObject *source_object, GAsyncResult *res, gpointer user_data)
{
  DocumentLoader *doclod = (DocumentLoader *) user_data;
  DocumentLoaderDetails *docloddet = DOCUMENT_LOADER_GET_PRIVATE(doclod);
  GError *error=NULL;
  gsize size;
  gchar *buffer;
  GFileInfo *info;
  gboolean converted_to_utf8 = FALSE;
  GFile *file = (GFile *) source_object;
  if (!g_file_load_contents_finish (file, res, &buffer, &size, NULL, &error)) {
    g_print("Error reading file. Gio error:%s",error->message);
    g_error_free(error);
    emit_signal (doclod, FALSE, NULL);
    return ;
  }
  gphpedit_debug_message (DEBUG_DOCUMENT,"Loaded %u bytes", size);
  gphpedit_debug_message (DEBUG_DOCUMENT,"BUFFER=\n%s\n-------------------------------------------", buffer);

  if (size) converted_to_utf8 = _document_loader_validate_and_convert_utf8_buffer(&buffer);

  info = g_file_query_info (file, INFO_FLAGS,G_FILE_QUERY_INFO_NONE, NULL, &error);
  if (!info){
    g_warning ("%s\n", error->message);
    emit_signal (doclod, FALSE, NULL);
    return;
  }
  documentable_replace_text (DOCUMENTABLE(docloddet->doc), buffer);
  g_object_set(docloddet->doc, "converted_to_utf8", converted_to_utf8, NULL);
  g_object_set(docloddet->doc, "read_only", !g_file_info_get_attribute_boolean (info,"access::can-write"), "can_modify", TRUE, NULL);
  g_object_set(docloddet->doc,"content_type", g_file_info_get_content_type (info),NULL);
  GIcon *icon = g_file_info_get_icon (info);
  g_object_set(docloddet->doc, "icon", icon, NULL);
  GTimeVal file_mtime;
  g_file_info_get_modification_time (info,&file_mtime);
  gint64 time = (((gint64) file_mtime.tv_sec) * G_USEC_PER_SEC) + file_mtime.tv_usec;
  g_object_set(docloddet->doc, "mtime", time, NULL);
  g_object_unref(info);
  emit_signal (doclod, TRUE, DOCUMENT(docloddet->doc));
}
