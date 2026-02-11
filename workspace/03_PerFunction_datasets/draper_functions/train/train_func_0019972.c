kkam_iv_resize (ViewerInfo *vi, GdkEventConfigure *ev)
{
  GdkPixmap *pix = NULL;
  GdkBitmap *bit = NULL;

  gkrellm_scale_pixbuf_to_pixmap(vi->pixbuf, &pix, &bit,
                      ev->width, ev->height);

  gtk_image_set_from_pixmap (GTK_IMAGE (vi->pmap), pix, bit);
  g_object_unref(G_OBJECT(pix));
  if (bit)
    g_object_unref(G_OBJECT(bit));

  return TRUE;
}
