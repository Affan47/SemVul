on_preview_image_key_pressed (GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
  PhotosPrintSetupPrivate *priv = PHOTOS_PRINT_SETUP (user_data)->priv;
  PhotosPrintPreview *preview = PHOTOS_PRINT_PREVIEW (widget);
  gfloat scale;

  scale = photos_print_preview_get_scale (preview);

  switch (event->keyval)
    {
    case GDK_KEY_KP_Add:
    case GDK_KEY_plus:

      scale *= 1.1;
      break;
    case GDK_KEY_KP_Subtract:
    case GDK_KEY_minus:

      scale *= 0.9;
      break;
    default:
      return FALSE;
      break;
    }

  gtk_range_set_value (GTK_RANGE (priv->scaling), 100*scale);

  return TRUE;
}
