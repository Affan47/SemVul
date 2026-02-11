command_stats_getTotalViews(flickcurl* fc, int argc, char *argv[])
{
  char* date = NULL;
  flickcurl_view_stats* view_stats;

  if(argc > 0)
    date = argv[1];

  view_stats = flickcurl_stats_getTotalViews(fc, date);
  if(!view_stats)
    return 1;

  fprintf(stdout, "%s: Total view stats\n", program);
  fprintf(stdout,
          "  Total: %d\n  Photos: %d\n  Photostreams: %d\n  Sets: %d\n  Collections: %d\n",
          view_stats->total, view_stats->photos, view_stats->photostreams,
          view_stats->sets, view_stats->collections);

  flickcurl_free_view_stats(view_stats);
  return 0;
}
