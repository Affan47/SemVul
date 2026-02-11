gt_encseq_charcount(const GtEncseq *encseq, GtUchar cc)
{
  gt_assert(encseq != NULL &&
            (unsigned int) cc < gt_alphabet_num_of_chars(encseq->alpha));
  if (encseq->hasmirror) {
    return encseq->headerptr.characterdistribution[cc]
             + encseq->headerptr.characterdistribution[GT_COMPLEMENTBASE(cc)];
  } else return encseq->headerptr.characterdistribution[cc];
}
