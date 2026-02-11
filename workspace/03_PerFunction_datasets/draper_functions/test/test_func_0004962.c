_gtk_marshal_BOOLEAN__OBJECT_STRING_STRING_BOXEDv (GClosure     *closure,
                                                   GValue       *return_value,
                                                   gpointer      instance,
                                                   va_list       args,
                                                   gpointer      marshal_data,
                                                   int           n_params,
                                                   GType        *param_types)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__OBJECT_STRING_STRING_BOXED) (gpointer     instance,
                                                                        gpointer     arg_0,
                                                                        gpointer     arg_1,
                                                                        gpointer     arg_2,
                                                                        gpointer     arg_3,
                                                                        gpointer     data);
  GCClosure *cc = (GCClosure*) closure;
  gpointer data1, data2;
  GMarshalFunc_BOOLEAN__OBJECT_STRING_STRING_BOXED callback;
  gpointer arg0;
  gpointer arg1;
  gpointer arg2;
  gpointer arg3;
  va_list args_copy;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);

  G_VA_COPY (args_copy, args);
  arg0 = (gpointer) va_arg (args_copy, gpointer);
  if (arg0 != NULL)
    arg0 = g_object_ref (arg0);
  arg1 = (gpointer) va_arg (args_copy, gpointer);
  if ((param_types[1] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg1 != NULL)
    arg1 = g_strdup (arg1);
  arg2 = (gpointer) va_arg (args_copy, gpointer);
  if ((param_types[2] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg2 != NULL)
    arg2 = g_strdup (arg2);
  arg3 = (gpointer) va_arg (args_copy, gpointer);
  if ((param_types[3] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg3 != NULL)
    arg3 = g_boxed_copy (param_types[3] & ~G_SIGNAL_TYPE_STATIC_SCOPE, arg3);
  va_end (args_copy);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = instance;
    }
  else
    {
      data1 = instance;
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__OBJECT_STRING_STRING_BOXED) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       arg0,
                       arg1,
                       arg2,
                       arg3,
                       data2);
  if (arg0 != NULL)
    g_object_unref (arg0);
  if ((param_types[1] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg1 != NULL)
    g_free (arg1);
  if ((param_types[2] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg2 != NULL)
    g_free (arg2);
  if ((param_types[3] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg3 != NULL)
    g_boxed_free (param_types[3] & ~G_SIGNAL_TYPE_STATIC_SCOPE, arg3);

  g_value_set_boolean (return_value, v_return);
}
