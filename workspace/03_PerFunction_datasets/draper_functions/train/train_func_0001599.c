unregister_slave_subprocess (pid_t child)
{


  slaves_entry_t *s = slaves;
  slaves_entry_t *s_end = s + slaves_count;

  for (; s < s_end; s++)
    if (s->used && s->child == child)
      s->used = 0;
}
