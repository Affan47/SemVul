value(const char *val)
{
  clear_selection();
  free_data();
  set_changed();

  if (!val)
    return;

  value_ = strdup(val);

  initial_load = 1;
  format();
  initial_load = 0;

  topline(0);
  leftline(0);
}
