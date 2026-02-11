local_notify_neighbour_1(int s, struct neighbour *neigh, int kind)
{
    char buf[512];
    int rc;

    rc = snprintf(buf, 512,
                  "%s neighbour %lx address %s "
                  "if %s reach %04x rxcost %d txcost %d cost %d\n",
                  local_kind(kind),


                  (unsigned long int)neigh,
                  format_address(neigh->address),
                  neigh->ifp->name,
                  neigh->reach,
                  neighbour_rxcost(neigh),
                  neighbour_txcost(neigh),
                  neighbour_cost(neigh));

    if(rc < 0 || rc >= 512)
        goto fail;

    rc = write_timeout(s, buf, rc);
    if(rc < 0)
        goto fail;
    return;

 fail:
    shutdown(s, 1);
    return;
}
