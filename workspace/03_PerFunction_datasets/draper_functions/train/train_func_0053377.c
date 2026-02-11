flush_neighbour_routes(struct neighbour *neigh)
{
    int i;

    i = 0;
    while(i < route_slots) {
        struct babel_route *r;
        r = routes[i];
        while(r) {
            if(r->neigh == neigh) {
                flush_route(r);
                goto again;
            }
            r = r->next;
        }
        i++;
    again:
        ;
    }
}
