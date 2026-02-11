gt_sam_alignment_delete(GtSamAlignment *sam_alignment)
{
  if (sam_alignment != NULL) {
    bam_destroy1(sam_alignment->s_alignment);
    gt_alphabet_delete(sam_alignment->alphabet);
    gt_free(sam_alignment->qual_buffer);
    gt_free(sam_alignment->seq_buffer);
    gt_free(sam_alignment);
  }
}
