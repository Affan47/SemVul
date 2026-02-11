document_scintilla_set_property (GObject      *object,
			      guint         prop_id,
			      const GValue *value,
			      GParamSpec   *pspec)
{
  Document_ScintillaDetails *docdet = DOCUMENT_SCINTILLA_GET_PRIVATE(object);

  switch (prop_id)
  {
    case PROP_CAN_MODIFY:
      gtk_scintilla_set_read_only(GTK_SCINTILLA(docdet->scintilla),
          !g_value_get_boolean (value));
      break;
    case PROP_CONVERTED_TO_UTF8:
      docdet->converted_to_utf8 = g_value_get_boolean (value);
      break;
    case PROP_TYPE:
      docdet->type = g_value_get_int (value);
      documentable_set_type(DOCUMENTABLE(object), docdet->type);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
