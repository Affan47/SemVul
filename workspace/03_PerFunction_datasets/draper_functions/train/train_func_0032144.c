cmp_peer_cons(mca_oob_tcp_component_peer_t *ptr)
{
    ptr->mod = NULL;
    OBJ_CONSTRUCT(&ptr->reachable, opal_bitmap_t);
    opal_bitmap_init(&ptr->reachable, 8);
}
