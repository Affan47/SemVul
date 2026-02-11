var_lookup (CSPARSE *parse, char *name)
{
  CS_LOCAL_MAP *map;
  char *c;
  char* retval;

  map = lookup_map (parse, name, &c);
  if (map)
  {
    if (map->type == CS_TYPE_VAR)
    {
      if (c == NULL)
      {
	return hdf_obj_value (map->h);
      }
      else
      {
	return hdf_get_value (map->h, c+1, NULL);
      }
    }


    else if (map->type == CS_TYPE_STRING)
    {
      return map->s;
    }
    else if (map->type == CS_TYPE_NUM)
    {
      char buf[40];
      if (map->s) return map->s;
      snprintf (buf, sizeof(buf), "%ld", map->n);
      map->s = strdup(buf);
      map->map_alloc = 1;
      return map->s;
    }
  }


  retval = hdf_get_value (parse->hdf, name, NULL);
  if (retval == NULL && parse->global_hdf != NULL) {
    retval = hdf_get_value (parse->global_hdf, name, NULL);
  }
  return retval;
}
