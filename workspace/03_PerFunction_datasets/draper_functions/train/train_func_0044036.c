init_floatparm(char *name,
		   double default_value,
		   double min_value,
		   double max_value)
{
  int id = -1;
  if (Next_floatparm == MAX_FLOATPARMS)
    fatal_error("init_floatparm: too many parms");
  else {
    id = Next_floatparm++;
    Floatparms[id].name = name;
    Floatparms[id].val = default_value;
    Floatparms[id].default_val = default_value;
    Floatparms[id].min = min_value;
    Floatparms[id].max = max_value;
  }
  return id;
}
