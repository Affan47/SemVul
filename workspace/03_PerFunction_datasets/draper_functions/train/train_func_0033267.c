dxf_e_POLYLINE(DxfGlobalData *global, DxfLocalData *local)
{
	G3DObject *object = NULL;
	G3DMaterial *material;
	guint32 flags;
	gint32 m, n, col;

	col = dxf_prop_get_int(local->eprop, 62, 254);
	material = dxf_color_get_material(global->model, col);
	if(material == NULL)
		material = local->edata->material;

	flags = dxf_prop_get_int(local->eprop, 70, 0);
	if(flags & DXF_POLY_POLYFACE) {
		object = g_new0(G3DObject, 1);
		object->name = g_strdup_printf("POLYFACE @ line %d",
			g3d_stream_line(global->stream));
		object->vertex_count = dxf_prop_get_int(local->eprop, 71, 0);
		object->vertex_data = g_new0(gfloat, 3 * object->vertex_count);
	} else if(flags & DXF_POLY_3D_POLYMESH) {
		m = dxf_prop_get_int(local->eprop, 71, 0);
		n = dxf_prop_get_int(local->eprop, 72, 0);
		object = g3d_primitive_mesh(n, m,
			(flags & DXF_POLY_CLOSED),
			(flags & DXF_POLY_N_CLOSED),
			material);
		object->name = g_strdup_printf("3D POLYMESH %d x %d @ line %d",
			m, n, g3d_stream_line(global->stream));
	}

	if(object)
		dxf_object_append(global, local, object);

	local->edata->object = object;
	local->edata->vertex_offset = 0;
	local->edata->polyline_flags = flags;
	local->edata->tmp_i1 = 0;
	return TRUE;
}
