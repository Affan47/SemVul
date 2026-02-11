allocate_internal(int n_verts)
{

	if (n_verts > n_allocated) {
		if (vert != NULL) {
			vm_free(vert);
			vert = NULL;
		}

		if (radius_list != NULL) {
			vm_free(radius_list);
			radius_list = NULL;
		}

		vert = (vertex *) vm_malloc( sizeof(vertex) * n_verts );
		radius_list = (float *) vm_malloc( sizeof(float) * n_verts );

		Verify( (vert != NULL) );
		Verify( (radius_list != NULL) );

		memset( vert, 0, sizeof(vertex) * n_verts );
		memset( radius_list, 0, sizeof(float) * n_verts );

		n_allocated = n_verts;
	}

	n_to_render = 0;
	use_radius = true;
}
