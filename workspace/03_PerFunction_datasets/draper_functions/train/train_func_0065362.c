mca_btl_self_component_close(void)
{
    OBJ_DESTRUCT(&mca_btl_self_component.self_lock);
    OBJ_DESTRUCT(&mca_btl_self_component.self_frags_eager);
    OBJ_DESTRUCT(&mca_btl_self_component.self_frags_send);
    OBJ_DESTRUCT(&mca_btl_self_component.self_frags_rdma);
    return OMPI_SUCCESS;
}
