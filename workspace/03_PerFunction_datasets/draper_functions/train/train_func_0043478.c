g_cclosure_user_marshal_VOID__STRING_STRING_STRING (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data) {
	typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING) (gpointer data1, const char* arg_1, const char* arg_2, const char* arg_3, gpointer data2);
	register GMarshalFunc_VOID__STRING_STRING_STRING callback;
	register GCClosure * cc;
	register gpointer data1;
	register gpointer data2;
	cc = (GCClosure *) closure;
	g_return_if_fail (n_param_values == 4);
	if (G_CCLOSURE_SWAP_DATA (closure)) {
		data1 = closure->data;
		data2 = param_values->data[0].v_pointer;
	} else {
		data1 = param_values->data[0].v_pointer;
		data2 = closure->data;
	}
	callback = (GMarshalFunc_VOID__STRING_STRING_STRING) (marshal_data ? marshal_data : cc->callback);
	callback (data1, g_value_get_string (param_values + 1), g_value_get_string (param_values + 2), g_value_get_string (param_values + 3), data2);
}
