brasero_data_project_node_signal (BraseroDataProject *self,
				  guint signal,
				  BraseroFileNode *node)
{
	GValue instance_and_params [2];
	GValue return_value;
	GValue *params;


	instance_and_params->g_type = 0;
	g_value_init (instance_and_params, G_TYPE_FROM_INSTANCE (self));
	g_value_set_instance (instance_and_params, self);


	params = instance_and_params + 1;
	params->g_type = 0;
	g_value_init (params, G_TYPE_POINTER);
	g_value_set_pointer (params, node);


	return_value.g_type = 0;
	g_value_init (&return_value, G_TYPE_BOOLEAN);
	g_value_set_boolean (&return_value, FALSE);

	g_signal_emitv (instance_and_params,
			brasero_data_project_signals [signal],
			0,
			&return_value);

	g_value_unset (instance_and_params);
	g_value_unset (params);


	if (signal == NAME_COLLISION_SIGNAL && BRASERO_FILE_NODE_VIRTUAL (node))
		return FALSE;

	return g_value_get_boolean (&return_value);
}
