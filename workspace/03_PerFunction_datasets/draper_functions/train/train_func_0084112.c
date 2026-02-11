invalidate_route(struct routeinfo *routehead, unsigned short node)
{
	struct routeinfo *route, *cheaproute = NULL;

	for (route = routehead->next; route; route=route->next)
	{
		if (route->router == node)
		{
			route->valid = 0;
		}
	}
	set_lowest_cost_route(routehead, node);
}
