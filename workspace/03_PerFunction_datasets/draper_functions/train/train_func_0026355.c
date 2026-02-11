_gtk_marshal_VOID__STRING_UINT_FLAGS_UINTv (GClosure     *closure,
                                            GValue       *return_value,
                                            gpointer      instance,
                                            va_list       args,
                                            gpointer      marshal_data,
                                            int           n_params,
                                            GType        *param_types)
{
  typedef void (*GMarshalFunc_VOID__STRING_UINT_FLAGS_UINT) (gpointer     instance,
                                                             gpointer     arg_0,
                                                             guint        arg_1,
                                                             guint        arg_2,
                                                             guint        arg_3,
                                                             gpointer     data);
  GCClosure *cc = (GCClosure*) closure;
  gpointer data1, data2;
  GMarshalFunc_VOID__STRING_UINT_FLAGS_UINT callback;
  gpointer arg0;
  guint arg1;
  guint arg2;
  guint arg3;
  va_list args_copy;

  G_VA_COPY (args_copy, args);
  arg0 = (gpointer) va_arg (args_copy, gpointer);
  if ((param_types[0] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg0 != NULL)
    arg0 = g_strdup (arg0);
  arg1 = (guint) va_arg (args_copy, guint);
  arg2 = (guint) va_arg (args_copy, guint);
  arg3 = (guint) va_arg (args_copy, guint);
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
  callback = (GMarshalFunc_VOID__STRING_UINT_FLAGS_UINT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            arg0,
            arg1,
            arg2,
            arg3,
            data2);
  if ((param_types[0] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg0 != NULL)
    g_free (arg0);
}
