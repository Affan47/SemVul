NET_Query_Init(void)
{
    if (query_context == NULL)
    {
        query_context = NET_NewContext();
        NET_AddModule(query_context, &net_sdl_module);
        net_sdl_module.InitClient();
    }

    free(targets);
    targets = NULL;
    num_targets = 0;

    printed_header = false;
}
