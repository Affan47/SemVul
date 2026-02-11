champlain_license_connect_view (ChamplainLicense *license,
    ChamplainView *view)
{
  g_return_if_fail (CHAMPLAIN_IS_LICENSE (license));

  license->priv->view = g_object_ref (view);

  g_signal_connect (view, "notify::map-source",
      G_CALLBACK (redraw_license_cb), license);
  g_signal_connect (view, "notify::width",
      G_CALLBACK (redraw_license_cb), license);
  g_signal_connect (view, "notify::height",
      G_CALLBACK (redraw_license_cb), license);
  redraw_license (license);
}
