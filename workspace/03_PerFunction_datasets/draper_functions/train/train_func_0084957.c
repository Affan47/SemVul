gst_sub_parse_dispose (GObject * object)
{
  GstSubParse *subparse = GST_SUBPARSE (object);

  GST_DEBUG_OBJECT (subparse, "cleaning up subtitle parser");

  switch (subparse->parser_type) {
    case GST_SUB_PARSE_FORMAT_QTTEXT:
      qttext_context_deinit (&subparse->state);
      break;
#ifndef GST_DISABLE_XML
    case GST_SUB_PARSE_FORMAT_SAMI:
      sami_context_deinit (&subparse->state);
      break;
#endif
    default:
      break;
  }

  if (subparse->encoding) {
    g_free (subparse->encoding);
    subparse->encoding = NULL;
  }

  if (subparse->detected_encoding) {
    g_free (subparse->detected_encoding);
    subparse->detected_encoding = NULL;
  }

  if (subparse->adapter) {
    g_object_unref (subparse->adapter);
    subparse->adapter = NULL;
  }

  if (subparse->textbuf) {
    g_string_free (subparse->textbuf, TRUE);
    subparse->textbuf = NULL;
  }

  GST_CALL_PARENT (G_OBJECT_CLASS, dispose, (object));
}
