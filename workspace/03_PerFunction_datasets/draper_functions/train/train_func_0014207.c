dump_attribute(bgav_yml_attr_t * a)
  {
  char * pos;

  bgav_dprintf( "%s=", a->name);

  pos = strchr(a->value, '"');

  if(pos)
    bgav_dprintf( "'%s'", a->value);
  else
    bgav_dprintf( "\"%s\"", a->value);

  }
