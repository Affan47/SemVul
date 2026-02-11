e_marshal_BOOLEAN__INT_INT_OBJECT_INT_INT_UINT (GClosure     *closure,
                                                GValue       *return_value G_GNUC_UNUSED,
                                                guint         n_param_values,
                                                const GValue *param_values,
                                                gpointer      invocation_hint G_GNUC_UNUSED,
                                                gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__INT_INT_OBJECT_INT_INT_UINT) (gpointer     data1,
                                                                         gint         arg_1,
                                                                         gint         arg_2,
                                                                         gpointer     arg_3,
                                                                         gint         arg_4,
                                                                         gint         arg_5,
                                                                         guint        arg_6,
                                                                         gpointer     data2);
  register GMarshalFunc_BOOLEAN__INT_INT_OBJECT_INT_INT_UINT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 7);

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
  callback = (GMarshalFunc_BOOLEAN__INT_INT_OBJECT_INT_INT_UINT) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_int (param_values + 1),
                       g_marshal_value_peek_int (param_values + 2),
                       g_marshal_value_peek_object (param_values + 3),
                       g_marshal_value_peek_int (param_values + 4),
                       g_marshal_value_peek_int (param_values + 5),
                       g_marshal_value_peek_uint (param_values + 6),
                       data2);

  g_value_set_boolean (return_value, v_return);
}
