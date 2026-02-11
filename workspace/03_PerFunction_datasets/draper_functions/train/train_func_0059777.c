i_plugin_finit(gs_memory_t *mem_raw, i_plugin_holder *list)
{   i_plugin_client_memory client_mem;
    i_plugin_make_memory(&client_mem, mem_raw);
    while (list != 0) {
        i_plugin_holder *h = list;
        list = h->next;
        h->I->d->finit(h->I, &client_mem);
        gs_free_object(mem_raw, h, "plugin_holder");
    }
}
