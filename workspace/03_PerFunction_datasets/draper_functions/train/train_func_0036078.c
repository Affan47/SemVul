clone(const geometry_batcher &geo)
{
	n_to_render = geo.n_to_render;
	n_allocated = geo.n_allocated;
	use_radius = geo.use_radius;

	if (n_allocated > 0) {
		vert = (vertex *) vm_malloc( sizeof(vertex) * n_allocated );
		radius_list = (float *) vm_malloc( sizeof(float) * n_allocated );

		memcpy( vert, geo.vert, sizeof(vertex) * n_allocated );
		memcpy( radius_list, geo.radius_list, sizeof(float) * n_allocated);
	} else {
		vert = NULL;
		radius_list = NULL;
	}
}
