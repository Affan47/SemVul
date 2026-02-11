dae_cb_geometry(DaeGlobalData *global, DaeLocalData *local)
{
	G3DObject *object;
	G3DMaterial *material;

	object = (G3DObject *)local->user_data;
	g_return_val_if_fail(object != NULL, FALSE);

	material = g3d_material_new();
	material->name = g_strdup("(default material)");
	object->materials = g_slist_append(object->materials, material);

	if(local->instance) {

		dae_xml_parse(global, local->instance,
			dae_chunks_geometry, local->level, object);
	}


	return dae_xml_parse(global, local->node, dae_chunks_geometry,
		local->level, object);
}
