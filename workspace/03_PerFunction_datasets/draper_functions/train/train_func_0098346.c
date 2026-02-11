gt_bioseq_show_sequence_as_fasta(GtBioseq *bs, unsigned long seqnum,
                                      unsigned long width, GtFile *outfp)
{
  char *seq = NULL;
  gt_assert(bs);
  gt_assert(seqnum < gt_bioseq_number_of_sequences(bs));
  seq = gt_bioseq_get_sequence(bs, seqnum);

  gt_fasta_show_entry(gt_bioseq_get_description(bs, seqnum),
                      seq,
                      gt_bioseq_get_sequence_length(bs, seqnum), width, outfp);

  gt_free(seq);
}
