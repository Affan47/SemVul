copy_write_sharing(Write_sharing *src)
{
    Write_sharing *ws;

    ws = malloc(sizeof(Write_sharing));
    if (ws == NULL) {
        fatal("malloc error for write_sharing\n");
    }
    *ws = *src;
    ws->parallel_section = copy_parallel_section(src->parallel_section);
    return ws;
}
