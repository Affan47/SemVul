bitset_stats_print_1 (FILE *file, const char *name,
                      struct bitset_type_info_struct *stats)
{
  if (!stats)
    return;

  fprintf (file, "%s:\n", name);
  fprintf (file, _("%u bitset_allocs, %u freed (%.2f%%).\n"),
           stats->allocs, stats->frees,
           stats->allocs ? 100.0 * stats->frees / stats->allocs : 0);
  fprintf (file, _("%u bitset_sets, %u cached (%.2f%%)\n"),
           stats->sets, stats->cache_sets,
           stats->sets ? 100.0 * stats->cache_sets / stats->sets : 0);
  fprintf (file, _("%u bitset_resets, %u cached (%.2f%%)\n"),
           stats->resets, stats->cache_resets,
           stats->resets ? 100.0 * stats->cache_resets / stats->resets : 0);
  fprintf (file, _("%u bitset_tests, %u cached (%.2f%%)\n"),
           stats->tests, stats->cache_tests,
           stats->tests ? 100.0 * stats->cache_tests / stats->tests : 0);

  fprintf (file, _("%u bitset_lists\n"), stats->lists);

  bitset_log_histogram_print (file, name, _("count log histogram\n"),
                              BITSET_LOG_COUNT_BINS, stats->list_counts);

  bitset_log_histogram_print (file, name, _("size log histogram\n"),
                              BITSET_LOG_SIZE_BINS, stats->list_sizes);

  bitset_percent_histogram_print (file, name, _("density histogram\n"),
                                  BITSET_DENSITY_BINS, stats->list_density);
}
