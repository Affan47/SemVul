gt_rcr_analyse_alignment_data(GtRcrEncoder *rcr_enc,
                                                GtTimer *timer,
                                                GtError *err)
{
  int had_err = 0;
  int32_t seq_id = 0;
  samfile_t *samfile = samopen(rcr_enc->samfilename, "rb", NULL);

  gt_assert(rcr_enc->sam_align != NULL);

  if (timer != NULL)
    gt_timer_show_progress(timer, "analyse sam/bam alignment data",
                           stdout);

  if (samfile == NULL) {
    gt_error_set(err, "Cannot open BAM file %s", rcr_enc->samfilename);
    had_err = -1;
  }

  while (!had_err &&
         samread(samfile, rcr_enc->sam_align) >= 0) {
    gt_assert(rcr_enc->sam_align != NULL);
    if (seq_id != rcr_enc->sam_align->core.tid) {
      rcr_enc->prev_readpos = 0;
      seq_id = rcr_enc->sam_align->core.tid;
      rcr_enc->cur_seq_startpos = gt_encseq_seqstartpos(rcr_enc->encseq,
                                                        (unsigned long) seq_id);
    }
    if (rcr_enc->prev_readpos > (unsigned long) rcr_enc->sam_align->core.pos) {
      gt_error_set(err, "file %s is not sorted", rcr_enc->samfilename);
      had_err = -1;
    }
    else {
      seq_id = rcr_enc->sam_align->core.tid;
      if (!(rcr_enc->sam_align->core.flag & BAM_FUNMAP))
        rcr_enc->numofreads++;
      else
        rcr_enc->numofunmappedreads++;

      had_err = rcr_get_read_infos(rcr_enc->sam_align, rcr_enc);
    }
  }


  rcr_enc->present_cigar_ops[ENDOFRECORD] = (unsigned long long)
                                              rcr_enc->numofreads;
  samclose(samfile);

  return had_err;
}
