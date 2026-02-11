store_true_exon(GtFeatureNode *fn, GtStrand predicted_strand,
                            GtRange *predicted_range, bool exondiff,
                            bool exondiffcollapsed,
                            GtTranscriptExons *exons_forward,
                            GtTranscriptExons *exons_reverse,
                            GtTranscriptCounts *counts_forward,
                            GtTranscriptCounts *counts_reverse,
                            GtTranscriptBittabs *exon_bittabs_forward,
                            GtTranscriptBittabs *exon_bittabs_reverse,
                            GtTranscriptEvaluators *exon_evaluators,
                            GtTranscriptEvaluators *exon_evaluators_collapsed)
{
  gt_assert(fn && predicted_range && exons_forward && exons_reverse);
  determine_true_exon(fn, predicted_strand, exondiff, exondiffcollapsed,
                      predicted_range,
                      gt_transcript_exons_get_all(exons_forward),
                      gt_transcript_exons_get_all(exons_reverse),
                      gt_transcript_counts_get_all(counts_forward),
                      gt_transcript_counts_get_all(counts_reverse),
                      gt_transcript_bittabs_get_all(exon_bittabs_forward),
                      gt_transcript_bittabs_get_all(exon_bittabs_reverse),
                      gt_transcript_evaluators_get_all(exon_evaluators),
                      gt_transcript_evaluators_get_all(
                                                    exon_evaluators_collapsed));
  switch (gt_feature_node_get_transcriptfeaturetype(fn)) {
    case TRANSCRIPT_FEATURE_TYPE_UNDETERMINED:
    case TRANSCRIPT_FEATURE_TYPE_SINGLE:
      determine_true_exon(fn, predicted_strand, exondiff, exondiffcollapsed,
                          predicted_range,
                          gt_transcript_exons_get_single(exons_forward),
                          gt_transcript_exons_get_single(exons_reverse),
                          gt_transcript_counts_get_single(counts_forward),
                          gt_transcript_counts_get_single(counts_reverse),
                          gt_transcript_bittabs_get_single(
                                                      exon_bittabs_forward),
                          gt_transcript_bittabs_get_single(
                                                      exon_bittabs_reverse),
                          gt_transcript_evaluators_get_single(exon_evaluators),
                          gt_transcript_evaluators_get_single(
                            exon_evaluators_collapsed));
      break;
    case TRANSCRIPT_FEATURE_TYPE_INITIAL:
      determine_true_exon(fn, predicted_strand, exondiff, exondiffcollapsed,
                          predicted_range,
                          gt_transcript_exons_get_initial(exons_forward),
                          gt_transcript_exons_get_initial(exons_reverse),
                          gt_transcript_counts_get_initial(counts_forward),
                          gt_transcript_counts_get_initial(counts_reverse),
                          gt_transcript_bittabs_get_initial(
                                                      exon_bittabs_forward),
                          gt_transcript_bittabs_get_initial(
                                                      exon_bittabs_reverse),
                          gt_transcript_evaluators_get_initial(exon_evaluators),
                          gt_transcript_evaluators_get_initial(
                            exon_evaluators_collapsed));
      break;
    case TRANSCRIPT_FEATURE_TYPE_INTERNAL:
      determine_true_exon(fn, predicted_strand, exondiff, exondiffcollapsed,
                          predicted_range,
                          gt_transcript_exons_get_internal(exons_forward),
                          gt_transcript_exons_get_internal(exons_reverse),
                          gt_transcript_counts_get_internal(counts_forward),
                          gt_transcript_counts_get_internal(counts_reverse),
                          gt_transcript_bittabs_get_internal(
                                                      exon_bittabs_forward),
                          gt_transcript_bittabs_get_internal(
                                                      exon_bittabs_reverse),
                          gt_transcript_evaluators_get_internal(
                                                      exon_evaluators),
                          gt_transcript_evaluators_get_internal(
                            exon_evaluators_collapsed));
      break;
    case TRANSCRIPT_FEATURE_TYPE_TERMINAL:
      determine_true_exon(fn, predicted_strand, exondiff, exondiffcollapsed,
                          predicted_range,
                          gt_transcript_exons_get_terminal(exons_forward),
                          gt_transcript_exons_get_terminal(exons_reverse),
                          gt_transcript_counts_get_terminal(counts_forward),
                          gt_transcript_counts_get_terminal(counts_reverse),
                          gt_transcript_bittabs_get_terminal(
                                                        exon_bittabs_forward),
                          gt_transcript_bittabs_get_terminal(
                                                        exon_bittabs_reverse),
                          gt_transcript_evaluators_get_terminal(
                                                        exon_evaluators),
                          gt_transcript_evaluators_get_terminal(
                            exon_evaluators_collapsed));
      break;
  }
}
