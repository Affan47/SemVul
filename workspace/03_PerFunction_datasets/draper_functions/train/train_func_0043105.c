gnu_obj_attrs_arg_type (int tag)
{


  if (tag == Tag_compatibility)
    return 3;
  else
    return (tag & 1) != 0 ? 2 : 1;
}
