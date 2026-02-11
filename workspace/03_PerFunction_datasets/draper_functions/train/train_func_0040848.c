gconf_client_get_pair    (GConfClient* client, const gchar* key,
                          GConfValueType car_type, GConfValueType cdr_type,
                          gpointer car_retloc, gpointer cdr_retloc,
                          GError** err)
{
  GError* error = NULL;
  GConfValue* val;

  g_return_val_if_fail (err == NULL || *err == NULL, FALSE);

  val = gconf_client_get (client, key, &error);

  if (val != NULL)
    {
      g_assert(error == NULL);


      if (gconf_value_pair_to_primitive_pair_destructive (val, car_type, cdr_type,
                                                          car_retloc, cdr_retloc,
                                                          &error))
        {
          g_assert (error == NULL);
          return TRUE;
        }
      else
        {
          g_assert (error != NULL);
          handle_error (client, error, err);
          return FALSE;
        }
    }
  else
    {
      if (error != NULL)
        {
          handle_error (client, error, err);
          return FALSE;
        }
      else
        return TRUE;
    }
}
