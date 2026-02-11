is_dump_and_scan(cli_ctx *ctx, off_t off, size_t fsize) {
    char *fname;
    const char *buf;
    int ofd, ret = CL_CLEAN;
    fmap_t *map = *ctx->fmap;

    if(!fsize) {
	cli_dbgmsg("ishield: skipping empty file\n");
	return CL_CLEAN;
    }
    if(!(fname = cli_gentemp(ctx->engine->tmpdir)))
	return CL_EMEM;

    if((ofd = open(fname, O_RDWR|O_CREAT|O_TRUNC|O_BINARY, S_IRUSR|S_IWUSR)) < 0) {
	cli_errmsg("ishield: failed to create file %s\n", fname);
	free(fname);
	return CL_ECREAT;
    }
    while(fsize) {
	size_t rd = MIN(fsize, map->pgsz);
	if(!(buf = fmap_need_off_once(map, off, rd))) {
	    cli_dbgmsg("ishield: read error\n");
	    ret = CL_EREAD;
	    break;
	}
	if(cli_writen(ofd, buf, rd) <= 0) {
	    ret = CL_EWRITE;
	    break;
	}
	fsize -= rd;
	off += rd;
    }
    if(!fsize) {
	cli_dbgmsg("ishield: extracted to %s\n", fname);
	if (lseek(ofd, 0, SEEK_SET) == -1) {
        cli_dbgmsg("ishield: call to lseek() failed\n");
        ret = CL_ESEEK;
    }
	ret = cli_magic_scandesc(ofd, ctx);
    }
    close(ofd);
    if(!ctx->engine->keeptmp)
	if(cli_unlink(fname)) ret = CL_EUNLINK;
    free(fname);
    return ret;
}
