gf_set_region_data(gf_region_data *rd,
  gf_t *gf,
  void *src,
  void *dest,
  int bytes,
  uint64_t val,
  int xor,
  int align)
{
  gf_internal_t *h = NULL;
  int wb;
  uint32_t a;
  unsigned long uls, uld;

  if (gf == NULL) {
    wb = 1;
  } else {
    h = gf->scratch;
    wb = (h->w)/8;
    if (wb == 0) wb = 1;
  }

  rd->gf = gf;
  rd->src = src;
  rd->dest = dest;
  rd->bytes = bytes;
  rd->val = val;
  rd->xor = xor;
  rd->align = align;

  uls = (unsigned long) src;
  uld = (unsigned long) dest;

  a = (align <= 16) ? align : 16;

  if (align == -1) {

    if (h != NULL && bytes % h->w != 0) {
      fprintf(stderr, "Error in region multiply operation.\n");
      fprintf(stderr, "The size must be a multiple of %d bytes.\n", h->w);
      exit(1);
    }

    rd->s_start = src;
    rd->d_start = dest;
    rd->s_top = (char*)src + bytes;
    rd->d_top = (char*)src + bytes;
    return;
  }

  if (uls % a != uld % a) {
    fprintf(stderr, "Error in region multiply operation.\n");
    fprintf(stderr, "The source & destination pointers must be aligned with respect\n");
    fprintf(stderr, "to each other along a %d byte boundary.\n", a);
    fprintf(stderr, "Src = 0x%lx.  Dest = 0x%lx\n", (unsigned long) src,
            (unsigned long) dest);
    exit(1);
  }

  if (uls % wb != 0) {
    fprintf(stderr, "Error in region multiply operation.\n");
    fprintf(stderr, "The pointers must be aligned along a %d byte boundary.\n", wb);
    fprintf(stderr, "Src = 0x%lx.  Dest = 0x%lx\n", (unsigned long) src,
            (unsigned long) dest);
    exit(1);
  }

  if (bytes % wb != 0) {
    fprintf(stderr, "Error in region multiply operation.\n");
    fprintf(stderr, "The size must be a multiple of %d bytes.\n", wb);
    exit(1);
  }

  uls %= a;
  if (uls != 0) uls = (a-uls);
  rd->s_start = (char*)rd->src + uls;
  rd->d_start = (char*)rd->dest + uls;
  bytes -= uls;
  bytes -= (bytes % align);
  rd->s_top = (char*)rd->s_start + bytes;
  rd->d_top = (char*)rd->d_start + bytes;

}
