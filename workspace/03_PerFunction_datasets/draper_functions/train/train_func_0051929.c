gnat_get_subrange_bounds (const_tree gnu_type, tree *lowval, tree *highval)
{
  *lowval = TYPE_MIN_VALUE (gnu_type);
  *highval = TYPE_MAX_VALUE (gnu_type);
}
