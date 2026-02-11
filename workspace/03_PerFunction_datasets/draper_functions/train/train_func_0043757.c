format5(struct fmtargs *args)
{
  struct fts3rec_offsets fo;
  struct fopd32 cur;
  struct ftver ftv;
  struct fopdi stat;
  struct fopd total;
  char *rec;
  u_int8 prot;
  u_int16 dstport;

  ftio_get_ver(&args->ftio, &ftv);

  if (ftio_check_xfield(&args->ftio, FT_XFIELD_DPKTS |
    FT_XFIELD_DOCTETS | FT_XFIELD_FIRST | FT_XFIELD_LAST |
    FT_XFIELD_PROT | FT_XFIELD_DSTPORT)) {
    fterr_warnx("Flow record missing required field for format.");
    return -1;
  }

  fts3rec_compute_offsets(&fo, &ftv);

  if (fopdi_alloc(&stat, 65536) < 0)
    return -1;

  bzero(&total, sizeof total);

  cur.flows = 1;

  while ((rec = ftio_read(&args->ftio))) {

    prot = *((u_int8*)(rec+fo.prot));


    if ((prot != IPPROTO_UDP) && (prot != IPPROTO_TCP))
      continue;

    CUR_GET_PLUS_FLOWS;

    TOTAL_INC;

    dstport = *((u_int16*)(rec+fo.dstport));

    STAT_INCA(dstport);

  }

  tbl_out1(args, 65536, &stat, &total, "port      ", FT_PATH_SYM_TCP_PORT);

  fopdi_free(&stat);

  return 0;

}
