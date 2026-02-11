g3d_model_load_full(G3DContext *context, const gchar *filename,
	guint32 flags)
{
	G3DModel *model;
	gdouble max_rad;

	model = g3d_model_new();

	g3d_context_update_progress_bar(context, 0.0, TRUE);

	if(g3d_plugins_load_model(context, filename, model))
	{
		g3d_context_update_progress_bar(context, 0.0, FALSE);


		if(!(flags & G3D_MODEL_NOCHECK))
			if(!g3d_model_check(model))
			{
				g3d_model_free(model);
				return NULL;
			}


		if(flags & G3D_MODEL_CENTER)
			g3d_model_center(model);


		max_rad = objects_max_radius(model->objects);


		objects_post_load(model->objects, max_rad, flags);


		if(model->filename == NULL)
			model->filename = g_strdup(filename);

		return model;
	}
	else
	{
		g3d_context_update_progress_bar(context, 0.0, FALSE);
		g3d_model_free(model);
	}

	return NULL;

}
