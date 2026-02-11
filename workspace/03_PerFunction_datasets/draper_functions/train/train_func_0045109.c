lwo_cb_SRFS(G3DIffGlobal *global, G3DIffLocal *local)
{
	LwoObject *obj;
	G3DMaterial *material;
	gchar buffer[512];

	obj = (LwoObject *)global->user_data;
	g_return_val_if_fail(obj != NULL, FALSE);

	while(local->nb > 0)
	{
		material = g3d_material_new();
		local->nb -= lwo_read_string(global->stream, buffer);
		material->name = g_strdup(buffer);
		global->model->materials = g_slist_append(global->model->materials,
			material);

	}

	return TRUE;
}
