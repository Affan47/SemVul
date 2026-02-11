build_route(struct phoneprov_file *pp_file, struct user *user, char *uri)
{
	struct http_route *route;

	if (!(route = ao2_alloc(sizeof(*route), route_destructor))) {
		return;
	}

	if (ast_string_field_init(route, 32)) {
		ast_log(LOG_ERROR, "Couldn't create string fields for %s\n", pp_file->format);
		route = unref_route(route);
		return;
	}

	ast_string_field_set(route, uri, S_OR(uri, pp_file->format));
	route->user = user;
	route->file = pp_file;

	ao2_link(http_routes, route);

	route = unref_route(route);
}
