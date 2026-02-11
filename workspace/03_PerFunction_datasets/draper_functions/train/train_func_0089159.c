gdict_source_dialog_get_property (GObject    *object,
				  guint       prop_id,
				  GValue     *value,
				  GParamSpec *pspec)
{
  GdictSourceDialog *dialog = GDICT_SOURCE_DIALOG (object);

  switch (prop_id)
    {
    case PROP_SOURCE_LOADER:
      g_value_set_object (value, dialog->loader);
      break;
    case PROP_SOURCE_NAME:
      g_value_set_string (value, dialog->source_name);
      break;
    case PROP_ACTION:
      g_value_set_int (value, dialog->action);
      break;
    default:
      break;
    }
}
