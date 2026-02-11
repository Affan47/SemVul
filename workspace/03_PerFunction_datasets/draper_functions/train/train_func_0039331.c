emit_asm_reloc(BuildCtx *ctx, int type, const char *sym)
{
  switch (ctx->mode) {
  case BUILD_elfasm:
    if (type)
      fprintf(ctx->fp, "\t.long %s-.-4\n", sym);
    else
      fprintf(ctx->fp, "\t.long %s\n", sym);
    break;
  case BUILD_coffasm:
    fprintf(ctx->fp, "\t.def %s; .scl 3; .type 32; .endef\n", sym);
    if (type)
      fprintf(ctx->fp, "\t.long %s-.-4\n", sym);
    else
      fprintf(ctx->fp, "\t.long %s\n", sym);
    break;
  default:
    fprintf(ctx->fp, "\t.long %s\n", sym);
    break;
  }
}
