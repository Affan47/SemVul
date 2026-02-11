eventRun(void)
{
  int i;

  for (i = 0; i < MAX_EVENTS; i++)
  {
    if (event_table[i].active && (event_table[i].when <= CurrentTime))
    {
      last_event_ran = event_table[i].name;
      event_table[i].func(event_table[i].arg);
      event_table[i].when = CurrentTime + event_table[i].frequency;
      event_time_min = -1;
    }
  }
}
