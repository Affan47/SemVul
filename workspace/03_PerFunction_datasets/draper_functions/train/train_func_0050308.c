runscanatpostrial(const GtEncseq *encseq,
                              GtEncseqReader *esr,
                              GtReadmode readmode,unsigned long startpos)
{
  unsigned long pos, totallength;
  GtUchar ccra, ccsr;

  totallength = encseq->logicaltotallength;
  gt_encseq_reader_reinit_with_readmode(esr,encseq,readmode,startpos);
  printf("runscanatpostrial with startpos %lu\n",startpos);
  for (pos=startpos; pos < totallength; pos++)
  {

    ccra = gt_encseq_get_encoded_char(encseq,pos,readmode);
    ccsr = gt_encseq_reader_next_encoded_char(esr);
    if (ccra != ccsr)
    {
      fprintf(stderr,"startpos = %lu"
                     " access=%s, mode=%s: position=%lu"
                     ": random access (correct) = %u != %u = "
                     " sequential read (wrong)\n",
                     startpos,
                     gt_encseq_accessname(encseq),
                     gt_readmode_show(readmode),
                     pos,
                     (unsigned int) ccra,
                     (unsigned int) ccsr);
      exit(GT_EXIT_PROGRAMMING_ERROR);
    }
  }
}
