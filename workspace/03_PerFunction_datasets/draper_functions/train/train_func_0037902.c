restore_resources(alloc_save_t * sprev, gs_ref_memory_t * mem)
{
    int code;
#ifdef DEBUG
    if (mem) {

        if_debug4m('u', (gs_memory_t *)mem, "[u%u]file_restore 0x%lx => 0x%lx for 0x%lx\n",
                   mem->space, (ulong)mem->streams,
                   (ulong)sprev->state.streams, (ulong) sprev);
    }
#endif


    code = font_restore(sprev);
    if (code < 0)
        return code;


    if (sprev->restore_names)
        names_restore(mem->gs_lib_ctx->gs_name_table, sprev);
    return 0;
}
