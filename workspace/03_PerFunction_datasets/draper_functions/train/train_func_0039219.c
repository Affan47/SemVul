tpaw_account_settings_get_int32 (TpawAccountSettings *settings,
    const gchar *param)
{
  GVariant *v;
  gint32 ret = 0;

  v = tpaw_account_settings_dup (settings, param);
  if (v == NULL)
    return 0;

  if (g_variant_is_of_type (v, G_VARIANT_TYPE_BYTE))
    ret = g_variant_get_byte (v);
  else if (g_variant_is_of_type (v, G_VARIANT_TYPE_INT32))
    ret = g_variant_get_int32 (v);
  else if (g_variant_is_of_type (v, G_VARIANT_TYPE_UINT32))
    ret = CLAMP (g_variant_get_uint32 (v), (guint) G_MININT32,
        G_MAXINT32);
  else if (g_variant_is_of_type (v, G_VARIANT_TYPE_INT64))
    ret = CLAMP (g_variant_get_int64 (v), G_MININT32, G_MAXINT32);
  else if (g_variant_is_of_type (v, G_VARIANT_TYPE_UINT64))
    ret = CLAMP (g_variant_get_uint64 (v), (guint64) G_MININT32, G_MAXINT32);
  else
    {
      gchar *tmp;

      tmp = g_variant_print (v, TRUE);
      DEBUG ("Unsupported type for param '%s': %s'", param, tmp);
      g_free (tmp);
    }

  g_variant_unref (v);
  return ret;
}
