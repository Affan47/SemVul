mark_type (tree type, enum escape_t escape_status)
{
  bitmap map = NULL;
  int uid;

  type = get_canon_type (type, true, true);
  if (!type)
    return NULL;

  switch (escape_status)
    {
    case EXPOSED_PARAMETER:
      map = global_types_exposed_parameter;
      break;
    case FULL_ESCAPE:
      map = global_types_full_escape;
      break;
    }

  uid = TYPE_UID (type);
  if (!bitmap_set_bit (map, uid))
    return type;
  else if (escape_status == FULL_ESCAPE)


    bitmap_set_bit (global_types_exposed_parameter, uid);

  return type;
}
