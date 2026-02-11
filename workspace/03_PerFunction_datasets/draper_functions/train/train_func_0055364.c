_gtk_marshal_VOID__BOOLEAN_BOOLEAN_BOOLEANv (GClosure     *closure,
                                             GValue       *return_value,
                                             gpointer      instance,
                                             va_list       args,
                                             gpointer      marshal_data,
                                             int           n_params,
                                             GType        *param_types)
{
  typedef void (*GMarshalFunc_VOID__BOOLEAN_BOOLEAN_BOOLEAN) (gpointer     instance,
                                                              gboolean     arg_0,
                                                              gboolean     arg_1,
                                                              gboolean     arg_2,
                                                              gpointer     data);
  GCClosure *cc = (GCClosure*) closure;
  gpointer data1, data2;
  GMarshalFunc_VOID__BOOLEAN_BOOLEAN_BOOLEAN callback;
  gboolean arg0;
  gboolean arg1;
  gboolean arg2;
  va_list args_copy;

  G_VA_COPY (args_copy, args);
  arg0 = (gboolean) va_arg (args_copy, gboolean);
  arg1 = (gboolean) va_arg (args_copy, gboolean);
  arg2 = (gboolean) va_arg (args_copy, gboolean);
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
  callback = (GMarshalFunc_VOID__BOOLEAN_BOOLEAN_BOOLEAN) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            arg0,
            arg1,
            arg2,
            data2);
}
