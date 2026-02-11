sw_contact_request_image_fetch (SwContact      *contact,
                             gboolean     delays_ready,
                             const gchar *key,
                             const gchar *url)
{
  RequestImageFetchClosure *closure;


  if (delays_ready)
    sw_contact_push_pending (contact);

  closure = g_slice_new0 (RequestImageFetchClosure);

  closure->key = g_intern_string (key);
  closure->contact = g_object_ref (contact);
  closure->delays_ready = delays_ready;

  SW_DEBUG (CONTACT, "Scheduling fetch for %s on: %s",
            url,
            sw_contact_get (closure->contact, "id"));
  sw_web_download_image_async (url,
                               (ImageDownloadCallback)_image_download_cb,
                               closure);
}
