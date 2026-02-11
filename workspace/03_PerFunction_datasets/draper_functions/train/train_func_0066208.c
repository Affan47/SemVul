rest_param_new_full (const char    *name,
                     RestMemoryUse  use,
                     gconstpointer  data,
                     gsize          length,
                     const char    *content_type,
                     const char    *filename)
{
  RestParam *param;

  param = g_slice_new0 (RestParam);

  if (use == REST_MEMORY_COPY) {
    data = g_memdup (data, length);
    use  = REST_MEMORY_TAKE;
  }

  param->name   = g_strdup (name);
  param->use    = use;
  param->data   = data;
  param->length = length;

  param->content_type = g_intern_string (content_type);
  param->filename     = g_strdup (filename);

  param->ref_count = 1;

  if (use == REST_MEMORY_TAKE) {
    param->owner         = (gpointer)data;
    param->owner_dnotify = g_free;
  }

  return param;
}
