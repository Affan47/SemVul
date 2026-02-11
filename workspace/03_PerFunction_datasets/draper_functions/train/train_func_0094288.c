gt_encseq_check_markpos(const GtEncseq *encseq)
{
  if (encseq->numofdbsequences > 1UL)
  {
    unsigned long *markpos, totallength, pos, currentseqnum = 0, seqnum;
    GtUchar currentchar;
    GtEncseqReader *esr;

    markpos = encseq2markpositions(encseq);
    totallength = encseq->logicaltotallength;
    esr = gt_encseq_create_reader_with_readmode(encseq, GT_READMODE_FORWARD, 0);

    for (pos=0; pos<totallength; pos++)
    {
      currentchar = gt_encseq_reader_next_encoded_char(esr);
      if (currentchar == (GtUchar) SEPARATOR)
      {
        currentseqnum++;
      } else
      {
        seqnum = gt_encseq_sep2seqnum(markpos, encseq->numofdbsequences,
                                      totallength, pos);
        if (seqnum != currentseqnum)
        {
          fprintf(stderr,"pos= %lu seqnum = %lu != %lu = currentseqnum\n",
                          pos,seqnum,currentseqnum);
          exit(GT_EXIT_PROGRAMMING_ERROR);
        }
      }
    }
    gt_encseq_reader_delete(esr);
    gt_free(markpos);
  }
}
