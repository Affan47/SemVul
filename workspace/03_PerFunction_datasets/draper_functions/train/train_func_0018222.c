layout_tracks(void *key, void *value, void *data,
                         GtError *err)
{
  unsigned long i,
                max = 50;
  GtTrack *track = NULL;
  GtLayoutTraverseInfo *lti = (GtLayoutTraverseInfo*) data;
  GtArray *list = (GtArray*) value;
  GtStr *gt_track_key;
  GtBlock *block;
  int had_err = 0;
  bool split = true;
  double tmp = 50;
  gt_assert(list);


  if (lti->layout->block_ordering_func) {
    gt_array_sort_stable_with_data(list, blocklist_block_compare,
                                   lti->layout);
  }


  block = *(GtBlock**) gt_array_get(list, 0);
  gt_track_key = gt_str_new_cstr((char*) key);


  if (gt_style_get_bool(lti->layout->style, "format", "split_lines", &split,
                         NULL, err) == GT_STYLE_QUERY_ERROR) {
    had_err = 1;
  }
  if (!had_err) {
    if (gt_style_get_num(lti->layout->style,
                         "format", "max_num_lines",
                         &tmp, NULL, err) == GT_STYLE_QUERY_ERROR) {
      had_err = 1;
    }
  }


  if (!had_err) {
    if (gt_style_get_bool(lti->layout->style, gt_block_get_type(block),
                          "split_lines",  &split, NULL,
                          err) == GT_STYLE_QUERY_ERROR) {
      had_err = 1;
    }
  }
  if (!had_err) {
    if (gt_style_get_num(lti->layout->style, gt_block_get_type(block),
                         "max_num_lines", &tmp, NULL,
                         err) == GT_STYLE_QUERY_ERROR) {
      had_err = 1;
    }
  }

  if (!had_err) {
    max = (unsigned long) tmp;
    track = gt_track_new(gt_track_key, max, split,
                         gt_line_breaker_captions_new(lti->layout,
                                                      lti->layout->width,
                                                      lti->layout->style));
    lti->layout->nof_tracks++;
    for (i = 0; !had_err && i < gt_array_size(list); i++) {
      block = *(GtBlock**) gt_array_get(list, i);
      had_err = gt_track_insert_block(track, block, err);
    }
  }
  if (!had_err) {
    gt_hashmap_add(lti->layout->tracks, gt_cstr_dup(gt_str_get(gt_track_key)),
                   track);
  }
  else
  {
    gt_track_delete(track);
  }

  gt_str_delete(gt_track_key);
  return had_err;
}
