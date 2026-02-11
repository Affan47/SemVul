blx_writecell(blxcontext_t *ctx, blxdata *cell, int cellrow, int cellcol) {
    unsigned char *uncompbuf=NULL,*outbuf=NULL;
    int bufsize, uncompsize, compsize;
    int status=0;
    int i,allundef;


    allundef=1;
    for(i=0; i < ctx->cell_xsize*ctx->cell_ysize; i++) {
	if(cell[i] > ctx->maxval)
	    ctx->maxval = cell[i];
	if(cell[i] < ctx->minval)
	    ctx->minval = cell[i];
	if(cell[i]!=BLX_UNDEF)
	    allundef=0;
    }

    if(allundef)
	return status;

    if(ctx->debug)
	BLXdebug2("Writing cell (%d,%d)\n",cellrow, cellcol);

    if(!ctx->open) {
	status=-3;
	goto error;
    }

    if((cellrow >= ctx->cell_rows) || (cellcol >= ctx->cell_cols)) {
	status=-2;
	goto error;
    }

    bufsize = sizeof(blxdata)*ctx->cell_xsize*ctx->cell_ysize+1024;
    uncompbuf = BLXmalloc(bufsize);
    outbuf = BLXmalloc(bufsize);

    uncompsize = blx_encode_celldata(ctx, cell, ctx->cell_xsize, uncompbuf, bufsize);
    compsize = compress_chunk(uncompbuf, uncompsize, outbuf, bufsize);
    if (compsize < 0)
    {
        BLXerror0("Couldn't compress chunk");
        status = -1;
        goto error;
    }

    if(uncompsize > ctx->maxchunksize)
	ctx->maxchunksize = uncompsize;

    ctx->cellindex[cellrow*ctx->cell_cols + cellcol].offset = BLXftell(ctx->fh);
    ctx->cellindex[cellrow*ctx->cell_cols + cellcol].datasize = uncompsize;
    ctx->cellindex[cellrow*ctx->cell_cols + cellcol].compdatasize = compsize;

    if((int)BLXfwrite(outbuf, 1, compsize, ctx->fh) != compsize) {
	status=-1;
	goto error;
    }

 error:
    if(uncompbuf)
	BLXfree(uncompbuf);
    if(outbuf)
	BLXfree(outbuf);
    return status;
}
