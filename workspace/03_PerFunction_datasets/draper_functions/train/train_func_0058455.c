mca_btl_tcp_component_init(int *num_btl_modules,
                                                   bool enable_progress_threads,
                                                   bool enable_mpi_threads)
{
    int ret = OMPI_SUCCESS;
    mca_btl_base_module_t **btls;
    *num_btl_modules = 0;


    ompi_free_list_init_new( &mca_btl_tcp_component.tcp_frag_eager,
                         sizeof (mca_btl_tcp_frag_eager_t) +
                         mca_btl_tcp_module.super.btl_eager_limit,
                         opal_cache_line_size,
                         OBJ_CLASS (mca_btl_tcp_frag_eager_t),
                         0,opal_cache_line_size,
                         mca_btl_tcp_component.tcp_free_list_num,
                         mca_btl_tcp_component.tcp_free_list_max,
                         mca_btl_tcp_component.tcp_free_list_inc,
                         NULL );

    ompi_free_list_init_new( &mca_btl_tcp_component.tcp_frag_max,
                         sizeof (mca_btl_tcp_frag_max_t) +
                         mca_btl_tcp_module.super.btl_max_send_size,
                         opal_cache_line_size,
                         OBJ_CLASS (mca_btl_tcp_frag_max_t),
                         0,opal_cache_line_size,
                         mca_btl_tcp_component.tcp_free_list_num,
                         mca_btl_tcp_component.tcp_free_list_max,
                         mca_btl_tcp_component.tcp_free_list_inc,
                         NULL );

    ompi_free_list_init_new( &mca_btl_tcp_component.tcp_frag_user,
                         sizeof (mca_btl_tcp_frag_user_t),
                         opal_cache_line_size,
                         OBJ_CLASS (mca_btl_tcp_frag_user_t),
                         0,opal_cache_line_size,
                         mca_btl_tcp_component.tcp_free_list_num,
                         mca_btl_tcp_component.tcp_free_list_max,
                         mca_btl_tcp_component.tcp_free_list_inc,
                         NULL );


    if(OMPI_SUCCESS != (ret = mca_btl_tcp_component_create_instances() )) {
        return 0;
    }


    if(OMPI_SUCCESS != (ret = mca_btl_tcp_component_create_listen(AF_INET) )) {
        return 0;
    }
#if OPAL_ENABLE_IPV6
    if((ret = mca_btl_tcp_component_create_listen(AF_INET6)) != OMPI_SUCCESS) {
        if (!(OMPI_ERR_IN_ERRNO == ret &&
              EAFNOSUPPORT == opal_socket_errno)) {
            opal_output (0, "mca_btl_tcp_component: IPv6 listening socket failed\n");
            return 0;
        }
    }
#endif


    if(OMPI_SUCCESS != (ret = mca_btl_tcp_component_exchange() )) {
        return 0;
    }

    btls = (mca_btl_base_module_t **)malloc(mca_btl_tcp_component.tcp_num_btls *
                  sizeof(mca_btl_base_module_t*));
    if(NULL == btls) {
        return NULL;
    }

#if OPAL_CUDA_SUPPORT
    mca_common_cuda_stage_one_init();
#endif

    memcpy(btls, mca_btl_tcp_component.tcp_btls, mca_btl_tcp_component.tcp_num_btls*sizeof(mca_btl_tcp_module_t*));
    *num_btl_modules = mca_btl_tcp_component.tcp_num_btls;
    return btls;
}
