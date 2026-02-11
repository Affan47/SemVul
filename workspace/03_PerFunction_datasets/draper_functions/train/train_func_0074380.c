gf_rdma_get_local_lid (struct ibv_context *context,
                       int32_t port)
{
        struct ibv_port_attr attr;

        if (ibv_query_port (context, port, &attr))
                return 0;

        return attr.lid;
}
