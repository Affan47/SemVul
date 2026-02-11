epsf_free(node_t * n)
{

    if (ND_shape_info(n))
	free(ND_shape_info(n));
}
