nsis_decomp(struct nsis_st *n) {
  int ret = CL_EFORMAT;
  switch(n->comp) {
  case COMP_BZIP2:
    n->bz.avail_in = n->nsis.avail_in;
    n->bz.next_in = n->nsis.next_in;
    n->bz.avail_out = n->nsis.avail_out;
    n->bz.next_out = n->nsis.next_out;
    switch (nsis_BZ2_bzDecompress(&n->bz)) {
    case BZ_OK:
      ret = CL_SUCCESS;
      break;
    case BZ_STREAM_END:
      ret = CL_BREAK;
    }
    n->nsis.avail_in = n->bz.avail_in;
    n->nsis.next_in = n->bz.next_in;
    n->nsis.avail_out = n->bz.avail_out;
    n->nsis.next_out = n->bz.next_out;
    break;
  case COMP_LZMA:
    n->lz.avail_in = n->nsis.avail_in;
    n->lz.next_in = n->nsis.next_in;
    n->lz.avail_out = n->nsis.avail_out;
    n->lz.next_out = n->nsis.next_out;
    switch (cli_LzmaDecode(&n->lz)) {
    case LZMA_RESULT_OK:
      ret = CL_SUCCESS;
      break;
    case LZMA_STREAM_END:
      ret = CL_BREAK;
    }
    n->nsis.avail_in = n->lz.avail_in;
    n->nsis.next_in = n->lz.next_in;
    n->nsis.avail_out = n->lz.avail_out;
    n->nsis.next_out = n->lz.next_out;
    break;
  case COMP_ZLIB:
    n->z.avail_in = n->nsis.avail_in;
    n->z.next_in = n->nsis.next_in;
    n->z.avail_out = n->nsis.avail_out;
    n->z.next_out = n->nsis.next_out;

    switch (nsis_inflate(&n->z)) {
    case Z_OK:
      ret = CL_SUCCESS;
      break;
    case Z_STREAM_END:
      ret = CL_BREAK;
    }
    n->nsis.avail_in = n->z.avail_in;
    n->nsis.next_in = n->z.next_in;
    n->nsis.avail_out = n->z.avail_out;
    n->nsis.next_out = n->z.next_out;
    break;
  }
  return ret;
}
