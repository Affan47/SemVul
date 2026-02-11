cli_unzip_single(cli_ctx *ctx, off_t lhoffl) {
  int ret=CL_CLEAN;
  unsigned int fu=0;
  uint32_t fsize;
  fmap_t *map = *ctx->fmap;

  cli_dbgmsg("in cli_unzip_single\n");
  fsize = (uint32_t)(map->len - lhoffl);
  if (lhoffl<0 || lhoffl>map->len || (sizeof(off_t)!=sizeof(uint32_t) && (off_t)fsize!=map->len - lhoffl)) {
    cli_dbgmsg("cli_unzip: bad offset\n");
    return CL_CLEAN;
  }
  if (fsize < SIZEOF_LH) {
    cli_dbgmsg("cli_unzip: file too short\n");
    return CL_CLEAN;
  }

  lhdr(map, lhoffl, fsize, &fu, 0, NULL, &ret, ctx, NULL, 0);

  return ret;
}
