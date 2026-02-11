xmt_resolve_routes(GF_XMTParser *parser)
{
	GF_Command *com;

	while (1) {
		com = (GF_Command *)gf_list_last(parser->unresolved_routes);
		if (!com) break;
		gf_list_rem_last(parser->unresolved_routes);
		switch (com->tag) {
		case GF_SG_ROUTE_DELETE:
		case GF_SG_ROUTE_REPLACE:
			com->RouteID = xmt_get_route(parser, com->unres_name, 0);
			if (!com->RouteID) {
				xmt_report(parser, GF_BAD_PARAM, "Cannot resolve GF_Route DEF %s", com->unres_name);
			}
			gf_free(com->unres_name);
			com->unres_name = NULL;
			com->unresolved = 0;
			break;
		}
	}
	while (gf_list_count(parser->inserted_routes)) gf_list_rem(parser->inserted_routes, 0);
}
