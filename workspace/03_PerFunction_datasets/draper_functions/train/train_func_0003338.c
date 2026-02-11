goa_provider_get_all (GAsyncReadyCallback callback,
                      gpointer            user_data)
{
  GList *extensions;
  GList *l;
  GIOExtensionPoint *extension_point;
  GetAllData *data;
  gint i;

  ensure_builtins_loaded ();

  data = g_slice_new0 (GetAllData);
  data->result = g_simple_async_result_new (NULL, callback, user_data,
      goa_provider_get_all);
  g_queue_init (&data->ret);


  extension_point = g_io_extension_point_lookup (GOA_PROVIDER_EXTENSION_POINT_NAME);
  extensions = g_io_extension_point_get_extensions (extension_point);

  for (l = extensions, i = 0; l != NULL; l = l->next, i++)
    {
      GIOExtension *extension = l->data;


      g_queue_push_head (&data->ret, g_object_new (g_io_extension_get_type (extension), NULL));
    }


  extension_point = g_io_extension_point_lookup (GOA_PROVIDER_FACTORY_EXTENSION_POINT_NAME);
  extensions = g_io_extension_point_get_extensions (extension_point);
  for (l = extensions, i = 0; l != NULL; l = l->next, i++)
    {
      GIOExtension *extension = l->data;
      goa_provider_factory_get_providers (g_object_new (g_io_extension_get_type (extension), NULL),
          get_providers_cb, data);
      data->pending_calls++;
    }

  get_all_check_done (data);
}
