write_ss_internal(ScmObj port, ScmObj obj, enum ScmOutputType otype)
{
    scm_write_ss_context ctx = {{0}};
    size_t i;

    ctx.next_index = 1;
    ctx.seen.size = 1 << 8;
    ctx.seen.ents = scm_malloc(ctx.seen.size * sizeof(scm_hash_entry));
    for (i = 0; i < ctx.seen.size; i++)
        ctx.seen.ents[i].key = SCM_INVALID;

    write_ss_scan(obj, &ctx);


    if (!HASH_EMPTY(ctx.seen))
        l_write_ss_ctx = &ctx;

    write_internal(port, obj, otype);

    l_write_ss_ctx = NULL;
    free(ctx.seen.ents);
}
