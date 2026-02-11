encode_string(void* vctx, ERL_NIF_TERM binary)
{
    encode_ctx* ctx = (encode_ctx*)vctx;
    ErlNifBinary bin;

    if(!enif_inspect_binary(ctx->env, binary, &bin)) {
        return NOMEM;
    }
    fill_buffer(ctx, "\"", 1);
    if (ctx->error) {
        return ctx->error;
    }
    yajl_string_encode2(fill_buffer, ctx, bin.data, bin.size);
    fill_buffer(ctx, "\"", 1);

    return ctx->error;
}
