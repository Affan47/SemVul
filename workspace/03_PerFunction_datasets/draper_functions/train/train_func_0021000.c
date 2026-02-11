dxf_color_get_material(G3DModel *model, gint32 aci)
{
	gchar *cname;
	G3DMaterial *material;

	cname = g_strdup_printf("color #%d", ABS(aci));
	material = get_material(model, cname);
	if(material != NULL) {
		g_free(cname);
		return material;
	}
	material = g3d_material_new();
	material->name = cname;
	model->materials = g_slist_append(model->materials, material);
	set_aci(material, ABS(aci));
#if DEBUG > 0
	g_debug("| color: %.2f %.2f %.2f", material->r, material->g, material->b);
#endif

	return material;
}
