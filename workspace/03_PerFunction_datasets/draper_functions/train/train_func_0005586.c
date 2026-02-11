mitsu_cpd70x_printer_end(stp_vars_t *v)
{

  if (*((const char*)((privdata.laminate->seq).data)) == 0x01) {


    int r, c;
    unsigned long seed = 1;


    for (c = 0 ; c < privdata.w_size ; c++) {
      for (r = 0 ; r < privdata.h_size + 12 ; r++) {
	int i = xrand(&seed) & 0x1f;
	if (i < 24)
	  stp_put16_be(0xab58, v);
	else if (i < 29)
	  stp_put16_be(0x286a, v);
	else
	  stp_put16_be(0x6c22, v);
      }
    }

    dyesub_nputc(v, 0x00, 512 - ((privdata.w_size * (privdata.h_size + 12) * 2) % 512));
  }
}
