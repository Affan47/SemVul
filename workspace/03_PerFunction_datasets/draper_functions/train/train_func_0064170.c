gs_fapi_init(gs_memory_t *mem)
{
    int code = 0;
    int i, num_servers = 0;
    gs_fapi_server **servs = NULL;
    const gs_fapi_server_init_func *gs_fapi_server_inits =
        gs_get_fapi_server_inits();

    while (gs_fapi_server_inits[num_servers]) {
        num_servers++;
    }

    servs =
        (gs_fapi_server **) gs_alloc_bytes_immovable(mem->non_gc_memory,
                                                     (num_servers +
                                                      1) *
                                                     sizeof(gs_fapi_server *),
                                                     "gs_fapi_init");
    if (!servs) {
        return_error(gs_error_VMerror);
    }

    for (i = 0; i < num_servers; i++) {
        gs_fapi_server_init_func *f =
            (gs_fapi_server_init_func *) & (gs_fapi_server_inits[i]);

        code = (*f) (mem, &(servs[i]));
        if (code != 0) {
            break;
        }


        servs[i]->client_ctx_p = NULL;
    }

    for (; i < num_servers + 1; i++) {
        servs[i] = NULL;
    }

    mem->gs_lib_ctx->fapi_servers = servs;

    return (code);
}
