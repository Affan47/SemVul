dxf_e_BLOCK(DxfGlobalData *global, DxfLocalData *local)
{
	G3DObject *object;
	const gchar *name;

	name = dxf_prop_get_str(local->eprop, 2, NULL);
	if(local->sid == DXF_ID_BLOCKS) {
		object = g_new0(G3DObject, 1);
		object->hide = TRUE;
		object->name = name ? g_strdup(name) :
			g_strdup_printf("unnamed block @ line %d",
				g3d_stream_line(global->stream));
		local->edata->block = object;
		global->model->objects = g_slist_append(global->model->objects,
			object);
		if(name)
			g_hash_table_insert(global->blocks, object->name, object);
	}
	return TRUE;
}
