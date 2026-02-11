is_string_selected (int grep_pass, const char *str, size_t len)
{
  const struct grep_task *gt = &grep_task[grep_pass];

  if (gt->pattern_count > 0)
    {
      size_t match_size;
      size_t match_offset;

      match_offset =
        gt->matcher->execute (gt->compiled_patterns, str, len,
                              &match_size, false);
      return (match_offset != (size_t) -1);
    }
  else
    return 0;
}
