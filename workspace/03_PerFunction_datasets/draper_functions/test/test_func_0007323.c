show_target(GT_UNUSED unsigned long pos, void *data)
{
  TargetInfo *ti = data;
  char *seq;
  gt_assert(ti);
  seq = gt_bioseq_get_sequence(ti->bioseq, ti->seqnum);
  gt_fasta_show_entry(gt_bioseq_get_description(ti->bioseq, ti->seqnum),
                      seq,
                      gt_bioseq_get_sequence_length(ti->bioseq, ti->seqnum), 0,
                      NULL);
  gt_free(seq);
  return true;
}
