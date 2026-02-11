multicharactercompare_withtest(const GtEncseq *encseq,
                                           GtReadmode readmode,
                                           unsigned long pos1,
                                           unsigned long pos2)
{
  GtEndofTwobitencoding ptbe1, ptbe2;
  GtCommonunits commonunits1;
  unsigned long commonunits2, twobitencodingstoppos1, twobitencodingstoppos2;
  int ret1, ret2;
  GtEncseqReader *esr1, *esr2;
  bool fwd = GT_ISDIRREVERSE(readmode) ? false : true,
       complement = GT_ISDIRCOMPLEMENT(readmode) ? true : false;

  esr1 = gt_encseq_create_reader_with_readmode(encseq,readmode,pos1);
  if (gt_encseq_has_twobitencoding_stoppos_support(encseq))
  {
    twobitencodingstoppos1 = gt_getnexttwobitencodingstoppos (fwd, esr1);
  } else
  {
    twobitencodingstoppos1 = GT_TWOBITENCODINGSTOPPOSUNDEF(encseq);
  }
  ptbe1.referstartpos = esr1->currentpos;
  esr1->currentpos = gt_encseq_extract2bitenc(&ptbe1,encseq,fwd,
                                              esr1->currentpos,
                                              twobitencodingstoppos1);
  esr2 = gt_encseq_create_reader_with_readmode(encseq,readmode,pos2);
  if (gt_encseq_has_twobitencoding_stoppos_support(encseq))
  {
    twobitencodingstoppos2 = gt_getnexttwobitencodingstoppos (fwd, esr2);
  } else
  {
    twobitencodingstoppos2 = GT_TWOBITENCODINGSTOPPOSUNDEF(encseq);
  }
  ptbe2.referstartpos = esr2->currentpos;
  esr2->currentpos = gt_encseq_extract2bitenc(&ptbe2,encseq,fwd,
                                              esr2->currentpos,
                                              twobitencodingstoppos2);
  gt_encseq_reader_delete(esr1);
  gt_encseq_reader_delete(esr2);
  ret1 = gt_encseq_compare_pairof_twobitencodings(fwd,complement,
                                                  &commonunits1,&ptbe1,&ptbe2);
  commonunits2 = (unsigned long) GT_UNITSIN2BITENC;
  if (GT_ISDIRREVERSE(readmode))
  {
    pos1 = GT_REVERSEPOS(encseq->totallength,pos1);
    pos2 = GT_REVERSEPOS(encseq->totallength,pos2);
  }
  ret2 = gt_encseq_check_comparetwostrings(encseq,fwd,complement,
                                           &commonunits2,pos1,pos2,0);
  if (ret1 != ret2 || commonunits2 != (unsigned long) commonunits1.common)
  {
    char buf1[GT_INTWORDSIZE+1], buf2[GT_INTWORDSIZE+1];

    fprintf(stderr,"fwd=%s,complement=%s: "
                   "pos1=%lu, pos2=%lu\n",
            fwd ? "true" : "false",
            complement ? "true" : "false",
            pos1,pos2);
    fprintf(stderr,"ret1=%d, ret2=%d\n",ret1,ret2);
    fprintf(stderr,"commonunits1=%u, commonunits2=%lu\n",
            commonunits1.common,commonunits2);
    gt_encseq_showatstartpos(stderr,fwd,complement,encseq,pos1);
    gt_bitsequence_tostring(buf1,ptbe1.tbe);
    fprintf(stderr,"v1=%s(unitsnotspecial=%u)\n",buf1,ptbe1.unitsnotspecial);
    gt_encseq_showatstartpos(stderr,fwd,complement,encseq,pos2);
    gt_bitsequence_tostring(buf2,ptbe2.tbe);
    fprintf(stderr,"v2=%s(unitsnotspecial=%u)\n",buf2,ptbe2.unitsnotspecial);
    exit(GT_EXIT_PROGRAMMING_ERROR);
  }
}
