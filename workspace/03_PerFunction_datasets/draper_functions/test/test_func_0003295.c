peas_extension_set_new_valist (PeasEngine  *engine,
                               GType        exten_type,
                               const gchar *first_property,
                               va_list      var_args)
{
  GParameter *parameters;
  guint n_parameters;
  PeasExtensionSet *set;

  g_return_val_if_fail (engine == NULL || PEAS_IS_ENGINE (engine), NULL);
  g_return_val_if_fail (G_TYPE_IS_INTERFACE (exten_type), NULL);

  if (!_valist_to_parameter_list (exten_type, first_property,
                                  var_args, &parameters, &n_parameters))
    {

      return NULL;
    }

  set = peas_extension_set_newv (engine, exten_type, n_parameters, parameters);

  while (n_parameters-- > 0)
    g_value_unset (&parameters[n_parameters].value);
  g_free (parameters);

  return set;
}
