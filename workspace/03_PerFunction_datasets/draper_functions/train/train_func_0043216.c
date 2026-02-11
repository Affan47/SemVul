gt_echodescriptionandsequence(const GtStrArray *filenametab,GtError *err)
{
  GtSeqIterator *seqit;
  char *desc = NULL;
  const GtUchar *sequence;
  unsigned long seqlen;
  bool haserr = false;
  int retval;

  seqit = gt_seq_iterator_sequence_buffer_new(filenametab, err);
  if (!seqit)
    return -1;
  while (true)
  {
    retval = gt_seq_iterator_next(seqit,
                                 &sequence,
                                 &seqlen,
                                 &desc,
                                 err);
    if (retval < 0)
    {
      haserr = true;
      break;
    }
    if (retval == 0)
    {
      break;
    }
    gt_symbolstring2fasta(stdout,desc,NULL,sequence,seqlen,70UL);
  }
  gt_seq_iterator_delete(seqit);
  return haserr ? -1 : 0;
}
