send_marginal_ihu(struct interface *ifp)
{
    struct neighbour *neigh;
    FOR_ALL_NEIGHBOURS(neigh) {
        if(ifp && neigh->ifp != ifp)
            continue;
        if(neigh->txcost >= 384 || (neigh->reach & 0xF000) != 0xF000)
            send_ihu(neigh, ifp);
    }
}
