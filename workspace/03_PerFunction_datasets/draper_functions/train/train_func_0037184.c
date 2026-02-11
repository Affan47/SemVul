schedule_set_pri (struct schedule_entry *e)
{
  e->pri = random ();
  if (e->pri < 1)
    e->pri = 1;
}
