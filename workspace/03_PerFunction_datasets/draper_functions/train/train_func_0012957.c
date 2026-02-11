g3d_primitive_mesh(guint32 m, guint32 n, gboolean wrap_m,
	gboolean wrap_n, G3DMaterial *material)
{
	G3DObject *object;
	G3DFace *face;
	gint32 x, y;

	object = g_new0(G3DObject, 1);
	object->vertex_count = m * n;
	object->vertex_data = g3d_vector_new(3, object->vertex_count);

	for(y = 0; y < (n - 1); y ++) {
		for(x = 0; x < (m - 1); x ++) {
			face = g3d_face_new_tri(material,
				y * m + x, y * m + x + 1, (y + 1) * m + x);
			object->faces = g_slist_prepend(object->faces, face);

			face = g3d_face_new_tri(material,
				(y + 1) * m + x, y * m + x + 1, (y + 1) * m + x + 1);
			object->faces = g_slist_prepend(object->faces, face);
		}
		if(wrap_n) {
			face = g3d_face_new_tri(material,
				(y + 1) * m - 1, y * m, (y + 2) * m - 1);
			object->faces = g_slist_prepend(object->faces, face);

			face = g3d_face_new_tri(material,
				(y + 2) * m - 1, y * m, (y + 1) * m);
			object->faces = g_slist_prepend(object->faces, face);
		}
	}
	if(wrap_m) {
		for(x = 0; x < (m - 1); x ++) {
			face = g3d_face_new_tri(material,
				(n - 1) * m + x, (n - 1) * m + x + 1, x);
			object->faces = g_slist_prepend(object->faces, face);

			face = g3d_face_new_tri(material,
				x, (n - 1) * m + x + 1, x + 1);
			object->faces = g_slist_prepend(object->faces, face);
		}
		if(wrap_n) {
			face = g3d_face_new_tri(material,
				n * m - 1, (n - 1) * m, m - 1);
			object->faces = g_slist_prepend(object->faces, face);

			face = g3d_face_new_tri(material,
				m - 1, (n - 1) * m, 0);
			object->faces = g_slist_prepend(object->faces, face);
		}
	}
	return object;
}
