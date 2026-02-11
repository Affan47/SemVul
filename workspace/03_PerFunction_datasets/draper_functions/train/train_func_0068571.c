protocol_summary_find(size_t level, const gchar *protoname)
{
  if (!protosummary_stats)
    return NULL;
  return protocol_stack_find(&protosummary_stats->stats_protos, level, protoname);
}
