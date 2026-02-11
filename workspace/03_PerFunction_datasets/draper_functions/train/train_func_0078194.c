lwo_cb_TAGS(G3DIffGlobal *global, G3DIffLocal *local)
{
	LwoObject *obj;
	G3DMaterial *material;
	gchar buffer[512];

	obj = (LwoObject *)global->user_data;
	g_return_val_if_fail(obj != NULL, FALSE);

	if(obj->ntags)
	{
		g_strfreev(obj->tags);
		obj->ntags = 0;
	}


	while(local->nb > 0)
	{
		local->nb -= lwo_read_string(global->stream, buffer);
		obj->ntags ++;
		obj->tags = g_realloc(obj->tags, (1 + obj->ntags) * sizeof(gchar *));
		obj->tags[obj->ntags - 1] = g_strdup(buffer);
		obj->tags[obj->ntags] = NULL;

		material = g3d_material_new();
		material->name = g_strdup(buffer);
		global->model->materials = g_slist_append(global->model->materials,
			material);
	}

	return TRUE;
}
