plugin_load_model_from_stream(G3DContext *context, G3DStream *stream,
	G3DModel *model, gpointer user_data)
{
	G3DImage *image = g_new0(G3DImage, 1);
	G3DObject *object;
	G3DMaterial *material;
	guint32 x, y, index;
	gfloat pcnt, prev_pcnt = 0.0;

	if(!g3d_plugins_load_image_from_stream(context, stream, image)) {
		g_free(image);
		return FALSE;
	}

	material = g3d_material_new();
	material->name = g_strdup("default material");
	material->r = 0.4;
	material->g = 0.4;
	material->b = 0.4;
	material->a = 1.0;
	model->materials = g_slist_append(model->materials, material);

	object = g3d_primitive_mesh(image->width, image->height, FALSE, FALSE,
		material);
	object->name = g_strdup("height field");
	model->objects = g_slist_append(model->objects, object);

#if DEBUG > 0
	g_debug("height field loader: image: %dx%dx%d",
		image->width, image->height, image->depth);
#endif

	for(y = 0; y < image->height; y ++) {
		for(x = 0; x < image->width; x ++) {
			index = y * image->width + x;

			object->vertex_data[index * 3 + 0] = x;
			object->vertex_data[index * 3 + 1] = y;
			switch(image->depth) {
				case 8:
					object->vertex_data[index * 3 + 2] = 0.0 +
						(gfloat)image->pixeldata[index] / 32.0;
					break;
				case 15:
				case 16:
					object->vertex_data[index*3+2] = 0.0 +
						*((guint16*)&image->pixeldata[index]);
					break;
				case 24:
				case 32:
					object->vertex_data[index * 3 + 2] = 0.0 +
						image->pixeldata[index * 4] / 32.0;
					break;
				default:
					break;
			}

			pcnt = (gfloat)(y * image->width + x) /
				(gfloat)(image->width * image->height);
			if((pcnt - prev_pcnt) > 0.01) {
				prev_pcnt = pcnt;
				g3d_context_update_progress_bar(context, pcnt, TRUE);
			}
			g3d_context_update_interface(context);
		}
	}

	return TRUE;
}
