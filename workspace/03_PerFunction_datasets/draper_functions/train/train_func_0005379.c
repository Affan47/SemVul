alloc_name_index_is_since_save(const gs_memory_t *mem,
                               uint nidx, const alloc_save_t *save)
{
    const name_string_t *pnstr;

    if (!save->restore_names)
        return false;
    pnstr = names_index_string_inline(mem->gs_lib_ctx->gs_name_table, nidx);
    if (pnstr->foreign_string)
        return false;
    return alloc_is_since_save(pnstr->string_bytes, save);
}
