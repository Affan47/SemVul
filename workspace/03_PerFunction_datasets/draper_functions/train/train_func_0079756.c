_check_and_update_parameters (GType * extractable_type, const gchar * id,
    GError ** error)
{
  gchar *real_id;
  GType old_type = *extractable_type;

  *extractable_type =
      ges_extractable_get_real_extractable_type_for_id (*extractable_type, id);

  if (*extractable_type == G_TYPE_NONE) {
    GST_WARNING ("No way to create a Asset for ID: %s, type: %s", id,
        g_type_name (old_type));

    if (error && *error == NULL)
      g_set_error (error, GES_ERROR, GES_ERROR_ASSET_WRONG_ID,
          "Wrong ID, can not find any extractable_type");
    return NULL;
  }

  real_id = ges_extractable_type_check_id (*extractable_type, id, error);
  if (real_id == NULL) {
    GST_WARNING ("Wrong ID %s, can not create asset", id);

    g_free (real_id);
    if (error && *error == NULL)
      g_set_error (error, GES_ERROR, GES_ERROR_ASSET_WRONG_ID, "Wrong ID");

    return NULL;
  }

  return real_id;
}
