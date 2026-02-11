inetCidrRouteTable_rowreq_ctx_init(inetCidrRouteTable_rowreq_ctx *
                                   rowreq_ctx, void *user_init_ctx)
{
    DEBUGMSGTL(("verbose:inetCidrRouteTable:inetCidrRouteTable_rowreq_ctx_init", "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);


    rowreq_ctx->data->rt_nexthop_type = 0;

    rowreq_ctx->data->rt_metric1 = -1;

    rowreq_ctx->data->rt_metric2 = -1;

    rowreq_ctx->data->rt_metric3 = -1;

    rowreq_ctx->data->rt_metric4 = -1;

    rowreq_ctx->data->rt_metric5 = -1;


    return MFD_SUCCESS;
}
