merge_out_clusters (unsigned int start,
				 unsigned int end)
{
  if (unlikely (end - start < 2))
    return;

  unsigned int cluster = out_info[start].cluster;

  for (unsigned int i = start + 1; i < end; i++)
    cluster = MIN (cluster, out_info[i].cluster);


  while (start && out_info[start - 1].cluster == out_info[start].cluster)
    start--;


  while (end < out_len && out_info[end - 1].cluster == out_info[end].cluster)
    end++;


  if (end == out_len)
    for (unsigned i = idx; i < len && info[i].cluster == out_info[end - 1].cluster; i++)
      info[i].cluster = cluster;

  for (unsigned int i = start; i < end; i++)
    out_info[i].cluster = cluster;
}
