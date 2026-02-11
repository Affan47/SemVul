gen_v7(struct ftio *ftio, int count)
{
  struct fts3rec_v7 rec_v7;
  int i;

  bzero(&rec_v7, sizeof rec_v7);

  rec_v7.dstaddr = 0xFFFF0000;
  rec_v7.dstport = 0xFF00;
  rec_v7.output = 0xFF00;
  rec_v7.Last = 0xFFFF0000;
  rec_v7.dst_as = 0xFF00;
  rec_v7.prot = 17;

  for (i = 0; i < count; ++i) {

    rec_v7.dPkts ++;
    rec_v7.dOctets ++;

    if (ftio_write(ftio, &rec_v7) < 0) {
      fterr_warnx("ftio_write(): failed");
      return -1;
    }

    rec_v7.srcaddr ++;
    rec_v7.dstaddr ++;

    rec_v7.srcport ++;
    rec_v7.dstport ++;

    rec_v7.input ++;
    rec_v7.output ++;

    rec_v7.First ++;
    rec_v7.Last ++;

    rec_v7.src_as ++;
    rec_v7.dst_as ++;

    rec_v7.router_sc ++;

  }

  return 0;

}
