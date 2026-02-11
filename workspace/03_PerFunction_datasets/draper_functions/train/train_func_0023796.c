init_misc()
{
  static int last = 0;

  if (max_logs < 1)
    max_logs = 1;
  if (logs)
    logs = nrealloc(logs, max_logs * sizeof(log_t));
  else
    logs = nmalloc(max_logs * sizeof(log_t));
  for (; last < max_logs; last++) {
    logs[last].filename = logs[last].chname = NULL;
    logs[last].mask = 0;
    logs[last].f = NULL;

    logs[last].szlast[0] = 0;
    logs[last].repeats = 0;

    logs[last].flags = 0;
  }
}
