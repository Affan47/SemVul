start_struct (location_t loc, enum tree_code code, tree name,
	      struct c_struct_parse_info **enclosing_struct_parse_info)
{


  tree ref = NULL_TREE;
  location_t refloc = UNKNOWN_LOCATION;

  if (name != NULL_TREE)
    ref = lookup_tag (code, name, 1, &refloc);
  if (ref && TREE_CODE (ref) == code)
    {
      if (TYPE_SIZE (ref))
	{
	  if (code == UNION_TYPE)
	    error_at (loc, "redefinition of %<union %E%>", name);
	  else
	    error_at (loc, "redefinition of %<struct %E%>", name);
	  if (refloc != UNKNOWN_LOCATION)
	    inform (refloc, "originally defined here");

	  ref = NULL_TREE;
	}
      else if (C_TYPE_BEING_DEFINED (ref))
	{
	  if (code == UNION_TYPE)
	    error_at (loc, "nested redefinition of %<union %E%>", name);
	  else
	    error_at (loc, "nested redefinition of %<struct %E%>", name);


	  ref = NULL_TREE;
	}
    }


  if (ref == NULL_TREE || TREE_CODE (ref) != code)
    {
      ref = make_node (code);
      pushtag (loc, name, ref);
    }

  C_TYPE_BEING_DEFINED (ref) = 1;
  TYPE_PACKED (ref) = flag_pack_struct;

  *enclosing_struct_parse_info = struct_parse_info;
  struct_parse_info = XNEW (struct c_struct_parse_info);
  struct_parse_info->struct_types.create (0);
  struct_parse_info->fields.create (0);
  struct_parse_info->typedefs_seen.create (0);


  if (warn_cxx_compat && (in_sizeof || in_typeof || in_alignof))
    warning_at (loc, OPT_Wc___compat,
		"defining type in %qs expression is invalid in C++",
		(in_sizeof
		 ? "sizeof"
		 : (in_typeof ? "typeof" : "alignof")));

  return ref;
}
