ges_project_add_encoding_profile (GESProject * project,
    GstEncodingProfile * profile)
{
  GList *tmp;
  GESProjectPrivate *priv;

  g_return_val_if_fail (GES_IS_PROJECT (project), FALSE);
  g_return_val_if_fail (GST_IS_ENCODING_PROFILE (profile), FALSE);

  priv = project->priv;
  for (tmp = priv->encoding_profiles; tmp; tmp = tmp->next) {
    GstEncodingProfile *tmpprofile = GST_ENCODING_PROFILE (tmp->data);

    if (g_strcmp0 (gst_encoding_profile_get_name (tmpprofile),
            gst_encoding_profile_get_name (profile)) == 0) {
      GST_INFO_OBJECT (project, "Already have profile: %s, replacing it",
          gst_encoding_profile_get_name (profile));

      gst_object_unref (tmp->data);
      tmp->data = gst_object_ref (profile);
      return TRUE;
    }
  }

  priv->encoding_profiles = g_list_prepend (priv->encoding_profiles,
      gst_object_ref (profile));

  return TRUE;
}
