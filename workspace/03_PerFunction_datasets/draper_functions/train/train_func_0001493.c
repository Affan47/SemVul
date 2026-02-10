libdef_func(BuildCtx *ctx, char *p, int arg)
{
  if (arg != LIBINIT_CF)
    ffasmfunc++;
  if (ctx->mode == BUILD_libdef) {
    if (modstate == 0) {
      fprintf(stderr, "Error: no module for function definition %s\n", p);
      exit(1);
    }
    if (regfunc == REGFUNC_NOREG) {
      if (optr+1 > obuf+sizeof(obuf)) {
	fprintf(stderr, "Error: output buffer overflow\n");
	exit(1);
      }
      *optr++ = LIBINIT_FFID;
    } else {
      if (arg != LIBINIT_ASM_) {
	if (modstate != 1) fprintf(ctx->fp, ",\n");
	modstate = 2;
	fprintf(ctx->fp, "  %s%s", arg ? LABEL_PREFIX_FFH : LABEL_PREFIX_CF, p);
      }
      if (regfunc != REGFUNC_NOREGUV) obuf[2]++;
      libdef_name(regfunc == REGFUNC_NOREGUV ? "" : p, arg);
    }
  } else if (ctx->mode == BUILD_ffdef) {
    fprintf(ctx->fp, "FFDEF(%s)\n", p);
  } else if (ctx->mode == BUILD_recdef) {
    if (strlen(p) > sizeof(funcname)-1) {
      fprintf(stderr, "Error: function name too long: '%s'\n", p);
      exit(1);
    }
    strcpy(funcname, p);
  } else if (ctx->mode == BUILD_vmdef) {
    int i;
    for (i = 1; p[i] && modname[i-1]; i++)
      if (p[i] == '_') p[i] = '.';
    fprintf(ctx->fp, "\"%s\",\n", p);
  } else if (ctx->mode == BUILD_bcdef) {
    if (arg != LIBINIT_CF)
      fprintf(ctx->fp, ",\n%d", find_ffofs(ctx, p));
  }
  ffid++;
  regfunc = REGFUNC_OK;
}
