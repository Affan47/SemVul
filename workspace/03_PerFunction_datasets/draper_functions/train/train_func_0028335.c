scintilla_marshal_VOID__INT_INT_STRING_INT_INT_INT_INT_INT (GClosure     *closure,
                                                            GValue       *return_value G_GNUC_UNUSED,
                                                            guint         n_param_values,
                                                            const GValue *param_values,
                                                            gpointer      invocation_hint G_GNUC_UNUSED,
                                                            gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__INT_INT_STRING_INT_INT_INT_INT_INT) (gpointer     data1,
                                                                         gint         arg_1,
                                                                         gint         arg_2,
                                                                         gpointer     arg_3,
                                                                         gint         arg_4,
                                                                         gint         arg_5,
                                                                         gint         arg_6,
                                                                         gint         arg_7,
                                                                         gint         arg_8,
                                                                         gpointer     data2);
  register GMarshalFunc_VOID__INT_INT_STRING_INT_INT_INT_INT_INT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 9);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__INT_INT_STRING_INT_INT_INT_INT_INT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_int (param_values + 1),
            g_marshal_value_peek_int (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_int (param_values + 4),
            g_marshal_value_peek_int (param_values + 5),
            g_marshal_value_peek_int (param_values + 6),
            g_marshal_value_peek_int (param_values + 7),
            g_marshal_value_peek_int (param_values + 8),
            data2);
}
