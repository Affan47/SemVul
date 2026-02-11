mca_btl_tcp_proc_create(ompi_proc_t* ompi_proc)
{
    int rc;
    size_t size;
    mca_btl_tcp_proc_t* btl_proc;
    uint64_t hash = ompi_rte_hash_name(&ompi_proc->proc_name);

    OPAL_THREAD_LOCK(&mca_btl_tcp_component.tcp_lock);
    rc = opal_hash_table_get_value_uint64(&mca_btl_tcp_component.tcp_procs,
                                          hash, (void**)&btl_proc);
    if(OMPI_SUCCESS == rc) {
        OPAL_THREAD_UNLOCK(&mca_btl_tcp_component.tcp_lock);
        return btl_proc;
    }

    btl_proc = OBJ_NEW(mca_btl_tcp_proc_t);
    if(NULL == btl_proc)
        return NULL;
    btl_proc->proc_ompi = ompi_proc;


    opal_hash_table_set_value_uint64(&mca_btl_tcp_component.tcp_procs,
                                     hash, btl_proc);
    OPAL_THREAD_UNLOCK(&mca_btl_tcp_component.tcp_lock);


    rc = ompi_modex_recv( &mca_btl_tcp_component.super.btl_version,
                                  ompi_proc,
                                  (void**)&btl_proc->proc_addrs,
                                  &size );
    if(rc != OMPI_SUCCESS) {
        BTL_ERROR(("mca_base_modex_recv: failed with return value=%d", rc));
        OBJ_RELEASE(btl_proc);
        return NULL;
    }
    if(0 != (size % sizeof(mca_btl_tcp_addr_t))) {
        BTL_ERROR(("mca_base_modex_recv: invalid size %lu: btl-size: %lu\n",
          (unsigned long) size, (unsigned long)sizeof(mca_btl_tcp_addr_t)));
        return NULL;
    }
    btl_proc->proc_addr_count = size / sizeof(mca_btl_tcp_addr_t);


    btl_proc->proc_endpoints = (mca_btl_base_endpoint_t**)
        malloc((1 + btl_proc->proc_addr_count) *
                sizeof(mca_btl_base_endpoint_t*));
    if(NULL == btl_proc->proc_endpoints) {
        OBJ_RELEASE(btl_proc);
        return NULL;
    }
    if(NULL == mca_btl_tcp_component.tcp_local && ompi_proc == ompi_proc_local()) {
        mca_btl_tcp_component.tcp_local = btl_proc;
    }
    {


        unsigned int i;
        for (i = 0; i < btl_proc->proc_addr_count; i++) {
            if (MCA_BTL_TCP_AF_INET == btl_proc->proc_addrs[i].addr_family) {
                btl_proc->proc_addrs[i].addr_family = AF_INET;
            }
#if OPAL_ENABLE_IPV6
            if (MCA_BTL_TCP_AF_INET6 == btl_proc->proc_addrs[i].addr_family) {
                btl_proc->proc_addrs[i].addr_family = AF_INET6;
            }
#endif
        }
    }
    return btl_proc;
}
