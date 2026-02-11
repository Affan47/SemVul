h5tools_dump_oid(FILE *stream, const h5tool_format_t *info,
        h5tools_context_t *ctx, hid_t oid)
{
    h5tools_str_t buffer;
    size_t        ncols = 80;
    hsize_t       curr_pos = ctx->sm_pos;


    HDmemset(&buffer, 0, sizeof(h5tools_str_t));

    if (info->line_ncols > 0)
        ncols = info->line_ncols;

    ctx->need_prefix = TRUE;
    h5tools_simple_prefix(stream, info, ctx, curr_pos, 0);

    h5tools_str_reset(&buffer);
    h5tools_str_append(&buffer, "%s %s %d %s", OBJID, BEGIN, oid, END);
    h5tools_render_element(stream, info, ctx, &buffer, &curr_pos, ncols, 0, 0);

    h5tools_str_close(&buffer);
}
