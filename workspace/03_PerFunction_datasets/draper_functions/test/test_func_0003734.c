route_interferes(struct babel_route *route, struct interface *ifp)
{
    switch(diversity_kind) {
    case DIVERSITY_NONE:
        return 1;
    case DIVERSITY_INTERFACE_1:
        return route->neigh->ifp == ifp;
    case DIVERSITY_CHANNEL_1:
    case DIVERSITY_CHANNEL:
        if(route->neigh->ifp == ifp)
            return 1;
        if(channels_interfere(ifp->channel, route->neigh->ifp->channel))
            return 1;
        if(diversity_kind == DIVERSITY_CHANNEL) {
            int i;
            for(i = 0; i < DIVERSITY_HOPS; i++) {
                if(route->channels[i] == 0)
                    break;
                if(channels_interfere(ifp->channel, route->channels[i]))
                    return 1;
            }
        }
        return 0;
    default:
        fprintf(stderr, "Unknown kind of diversity.\n");
        return 1;
    }
}
