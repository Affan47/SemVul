p400_block_init_func(stp_vars_t *v)
{
  int wide = (strcmp(privdata.pagesize, "c8x10") == 0
		  || strcmp(privdata.pagesize, "C6") == 0);

  stp_zprintf(v, "\033Z%c", '3' - privdata.plane + 1);
  if (wide)
    {
      stp_put16_be(privdata.h_size - privdata.block_max_h - 1, v);
      stp_put16_be(privdata.w_size - privdata.block_max_w - 1, v);
      stp_put16_be(privdata.block_max_h - privdata.block_min_h + 1, v);
      stp_put16_be(privdata.block_max_w - privdata.block_min_w + 1, v);
    }
  else
    {
      stp_put16_be(privdata.block_min_w, v);
      stp_put16_be(privdata.block_min_h, v);
      stp_put16_be(privdata.block_max_w - privdata.block_min_w + 1, v);
      stp_put16_be(privdata.block_max_h - privdata.block_min_h + 1, v);
    }
  dyesub_nputc(v, '\0', 53);
}
