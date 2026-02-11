umac_delete(umac_ctx_t ctx)

{
    char bytes_to_sub;

    if (ctx) {
        if (ALLOC_BOUNDARY) {
            bytes_to_sub = *((char *)ctx - 1);
            ctx = (umac_ctx_t)((char *)ctx - bytes_to_sub);
        }
        free(ctx);
    }
    return (1);
}
