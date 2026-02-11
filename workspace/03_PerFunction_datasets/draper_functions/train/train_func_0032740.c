x3ds_cb_0xA000(x3ds_global_data *global, x3ds_parent_data *parent)
{
	G3DMaterial *material;
	gchar buffer[1024];

	g_return_val_if_fail(parent->object, FALSE);

	parent->nb -= x3ds_read_cstr(global->stream, buffer);
	material = (G3DMaterial *)(parent->object);

	material->name = g_strdup(buffer);

	return TRUE;
}
