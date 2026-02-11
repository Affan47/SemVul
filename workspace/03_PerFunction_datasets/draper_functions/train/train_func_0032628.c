basic_stats_dump(const basic_stats_t *tf_stat)
{
  gchar *msg;
  gchar *msg_time;
  if (!tf_stat)
    return g_strdup("basic_stats_t NULL");

  msg_time = timeval_to_str (tf_stat->last_time);
  msg = g_strdup_printf("avg: %f, avg_acc: %f, total: %f, avg_size: %f, "
                        "packets: %lu, last heard: %s",
                        tf_stat->average,
                        tf_stat->aver_accu,
                        tf_stat->accumulated,
                        tf_stat->avg_size,
                        tf_stat->accu_packets,
                        msg_time);

  g_free(msg_time);
  return msg;
}
