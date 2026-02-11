cp_type_quals (tree type)
{
  type = strip_array_types (type);
  if (type == error_mark_node)
    return TYPE_UNQUALIFIED;
  return TYPE_QUALS (type);
}
