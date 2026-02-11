gs_getiodevice(const gs_memory_t *mem, int index)
{
    gs_lib_ctx_t *libctx = gs_lib_ctx_get_interp_instance(mem);

    if (libctx == NULL || libctx->io_device_table == NULL ||
        index < 0      || index >= gx_io_device_table_count)
        return 0;
    return libctx->io_device_table[index];
}
