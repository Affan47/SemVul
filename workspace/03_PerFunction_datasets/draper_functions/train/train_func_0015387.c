write_behind(struct testcase *test, int convert)
{
  char *writebuf;
  int count;
  int ct;
  char *p;
  int c;
  struct bf *b;
  struct tftphdr *dp;

  b = &bfs[nextone];
  if (b->counter < -1)
    return 0;

  if(!test->ofile) {
    char outfile[256];
    snprintf(outfile, sizeof(outfile), "log/upload.%ld", test->testno);
    test->ofile=open(outfile, O_CREAT|O_RDWR, 0777);
    if(test->ofile == -1) {
      logmsg("Couldn't create and/or open file %s for upload!", outfile);
      return -1;
    }
  }

  count = b->counter;
  b->counter = BF_FREE;
  dp = &b->buf.hdr;
  nextone = !nextone;
  writebuf = dp->th_data;

  if (count <= 0)
    return -1;

  if (convert == 0)
    return write(test->ofile, writebuf, count);

  p = writebuf;
  ct = count;
  while (ct--) {
    c = *p++;
    if (prevchar == '\r') {
      if (c == '\n')
        lseek(test->ofile, -1, SEEK_CUR);
      else
        if (c == '\0')
          goto skipit;

    }


    if(1 != write(test->ofile, &c, 1))
      break;
    skipit:
    prevchar = c;
  }
  return count;
}
