exo_helper_chooser_dialog_get_type (void)
{
  static GType type = G_TYPE_INVALID;

  if (G_UNLIKELY (type == G_TYPE_INVALID))
    {
      static const GTypeInfo info =
      {
        sizeof (ExoHelperChooserDialogClass),
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        sizeof (ExoHelperChooserDialog),
        0,
        (GInstanceInitFunc) exo_helper_chooser_dialog_init,
        NULL,
      };

      type = g_type_register_static (XFCE_TYPE_TITLED_DIALOG, I_("ExoHelperChooserDialog"), &info, 0);
    }

  return type;
}
