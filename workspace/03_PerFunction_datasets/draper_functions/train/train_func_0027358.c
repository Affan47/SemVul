analysis_frame_unref(analysis_frame_t * frame_analysis) {

  analysis_frame_t * return_list;

  if (frame_analysis == NULL)
    return frame_analysis;


  g_return_val_if_fail(frame_analysis->ref_count > 0, NULL);


  frame_analysis->ref_count--;


  if (frame_analysis->ref_count == 0) {

    return_list = analysis_frame_unref(frame_analysis->next_frame_analysis);
    frame_analysis->next_frame_analysis = NULL;

    frame_analysis->gate_analyses = analysis_gate_unref(frame_analysis->gate_analyses);
    g_free(frame_analysis);
    frame_analysis = NULL;
  } else
    return_list = frame_analysis;

  return return_list;
}
