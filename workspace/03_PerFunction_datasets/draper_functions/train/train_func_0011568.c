gf_sg_route_set_name(GF_Route *route, char *name)
{
	GF_Route *ptr;
	if (!name || !route) return GF_BAD_PARAM;
	ptr = gf_sg_route_find_by_name(route->graph, name);
	if (ptr) return GF_BAD_PARAM;
	if (route->name) gf_free(route->name);
	route->name = gf_strdup(name);
	return GF_OK;
}
