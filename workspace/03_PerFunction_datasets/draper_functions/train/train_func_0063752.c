check_format_string (tree fntype, unsigned HOST_WIDE_INT format_num,
		     int flags, bool *no_add_attrs, int expected_format_type)
{
  unsigned HOST_WIDE_INT i;
  bool is_objc_sref, is_target_sref, is_char_ref;
  tree ref;
  int fmt_flags;
  function_args_iterator iter;

  i = 1;
  FOREACH_FUNCTION_ARGS (fntype, ref, iter)
    {
      if (i == format_num)
	break;
      i++;
    }

  if (!ref
      || !valid_stringptr_type_p (ref))
    {
      if (!(flags & (int) ATTR_FLAG_BUILT_IN))
	error ("format string argument is not a string type");
      *no_add_attrs = true;
      return false;
    }


  if (expected_format_type < 0)
    return true;


  is_char_ref =
    (TYPE_MAIN_VARIANT (TREE_TYPE (ref)) == char_type_node);

  fmt_flags = format_flags (expected_format_type);
  is_objc_sref = is_target_sref = false;
  if (!is_char_ref)
    is_objc_sref = objc_string_ref_type_p (ref);

  if (!(fmt_flags & FMT_FLAG_PARSE_ARG_CONVERT_EXTERNAL))
    {
      if (is_char_ref)
	return true;
      else
	{

	  if (is_objc_sref)
	    error ("found a %<%s%> reference but the format argument should"
		   " be a string", format_name (gcc_objc_string_format_type));
	  else
	    error ("found a %qT but the format argument should be a string",
		   ref);
	  *no_add_attrs = true;
	  return false;
	}
    }


  if (is_char_ref)
    {
      error ("format argument should be a %<%s%> reference but"
	     " a string was found", format_name (expected_format_type));
      *no_add_attrs = true;
      return false;
    }


  if (!is_objc_sref)
    is_target_sref = (*targetcm.string_object_ref_type_p) ((const_tree) ref);

  if (expected_format_type == (int) gcc_objc_string_format_type
      && (is_objc_sref || is_target_sref))
    return true;


  if (first_target_format_type
      && expected_format_type >= first_target_format_type
      && is_target_sref)
    return true;
  else
    {
      error ("format argument should be a %<%s%> reference",
	      format_name (expected_format_type));
      *no_add_attrs = true;
      return false;
    }

  gcc_unreachable ();
}
