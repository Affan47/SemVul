browse_cb (GrlSource *source,
	   guint browse_id,
	   GrlMedia *media,
	   guint remaining,
	   gpointer user_data,
	   const GError *error)
{

  if (error) {
    g_error ("Browse operation failed. Reason: %s", error->message);
  }


  if (media) {

    const gchar *title = grl_media_get_title (media);


    if (GRL_IS_MEDIA_BOX (media)) {
      guint childcount = grl_media_box_get_childcount (GRL_MEDIA_BOX (media));
      g_debug ("\t Got '%s' (container with %d elements)", title, childcount);
    } else {
      guint seconds = grl_media_get_duration (media);
      const gchar *url = grl_media_get_url (media);
      g_debug ("\t Got '%s' (media - length: %d seconds)", title, seconds);
      g_debug ("\t\t URL: %s", url);
    }
    g_object_unref (media);
  }


  if (remaining == 0) {
    g_debug ("Browse operation finished!");
  }
}
