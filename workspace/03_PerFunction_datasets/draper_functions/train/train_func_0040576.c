rc3_emit_offset(regcomp_ctx *ctx, int offset)
{
    if (offset > REGEXP_OFFSET_MAX) {
        Scm_Error("regexp too large.  consider splitting it up: %50.1S",
                  SCM_OBJ(ctx->rx));
    }

    if (ctx->emitp) {
        SCM_ASSERT(ctx->codep < ctx->codemax-1);
        ctx->code[ctx->codep++] = (offset>>8) & 0xff;
        ctx->code[ctx->codep++] = offset & 0xff;
    } else {
        ctx->codemax+=2;
    }
}
