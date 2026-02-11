gt_checkandresetstorematch(GT_UNUSED uint64_t queryunit,
                             Storematchinfo *storeonline,
                             Storematchinfo *storeoffline)
{
  unsigned long seqnum, countmatchseq = 0,
    numofdbsequences = gt_encseq_num_of_sequences(storeonline->encseq);

  for (seqnum = 0; seqnum < numofdbsequences; seqnum++)
  {
#ifndef NDEBUG
    if (GT_ISIBITSET(storeonline->hasmatch,seqnum) &&
        !GT_ISIBITSET(storeoffline->hasmatch,seqnum))
    {
      fprintf(stderr,"query " Formatuint64_t " refseq %lu: "
                     "online has match but offline not\n",
                     PRINTuint64_tcast(queryunit),seqnum);
      exit(GT_EXIT_PROGRAMMING_ERROR);
    }
    if (!GT_ISIBITSET(storeonline->hasmatch,seqnum) &&
        GT_ISIBITSET(storeoffline->hasmatch,seqnum))
    {
      fprintf(stderr,"query " Formatuint64_t " refseq %lu: "
                     "offline has match but online not\n",
                     PRINTuint64_tcast(queryunit),seqnum);
      exit(GT_EXIT_PROGRAMMING_ERROR);
    }
#endif
    if (GT_ISIBITSET(storeonline->hasmatch,seqnum))
    {
      countmatchseq++;
    }
  }
  GT_CLEARBITTAB(storeonline->hasmatch,numofdbsequences);
  GT_CLEARBITTAB(storeoffline->hasmatch,numofdbsequences);
  printf("matching sequences: %lu\n",countmatchseq);
}
