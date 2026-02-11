lwo_cb_SPEC(G3DIffGlobal *global, G3DIffLocal *local)
{
	G3DMaterial *material;
	gfloat tmpf;

	material = (G3DMaterial *)local->object;
	g_return_val_if_fail(material != NULL, FALSE);

	if(global->flags & LWO_FLAG_LWO2)
	{
		tmpf = 1.0 - g3d_stream_read_float_be(global->stream);
		local->nb -= 4;
	}
	else
	{
		tmpf = 1.0 - (gfloat)g3d_stream_read_int16_be(global->stream) / 256.0;
		local->nb -= 2;
	}

	material->specular[0] = material->r * tmpf;
	material->specular[1] = material->g * tmpf;
	material->specular[2] = material->b * tmpf;

	return TRUE;
}
