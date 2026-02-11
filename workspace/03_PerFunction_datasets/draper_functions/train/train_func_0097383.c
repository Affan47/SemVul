adjust_best_info_with_junk_predicate (CutSequenceMatcher *matcher,
                                      gboolean should_junk,
                                      CutSequenceMatchInfo *best_info,
                                      guint from_begin, guint from_end,
                                      guint to_begin, guint to_end)
{
    CutSequenceMatcherPrivate *priv;

    priv = CUT_SEQUENCE_MATCHER_GET_PRIVATE(matcher);

    while (best_info->from_index > from_begin &&
           best_info->to_index > to_begin &&
           check_junk(priv, should_junk, best_info->to_index - 1) &&
           equal_content(priv,
                         best_info->from_index - 1,
                         best_info->to_index - 1)) {
        best_info->from_index--;
        best_info->to_index--;
        best_info->size++;
    }

    while (best_info->from_index + best_info->size + 1 < from_end &&
           best_info->to_index + best_info->size + 1 < to_end &&
           check_junk(priv,
                      should_junk,
                      best_info->to_index + best_info->size) &&
           equal_content(priv,
                         best_info->from_index + best_info->size,
                         best_info->to_index + best_info->size)) {
        best_info->size++;
    }
}
