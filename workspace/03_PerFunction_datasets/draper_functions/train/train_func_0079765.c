build_qualified_type (tree type, int type_quals)
{
  tree t;


  t = get_qualified_type (type, type_quals);


  if (!t)
    {
      t = build_type_copy (type);
      set_type_quals (t, type_quals);
    }

  return t;
}
