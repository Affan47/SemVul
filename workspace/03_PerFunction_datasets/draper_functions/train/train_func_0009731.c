member_function_or_else (tree ctype, tree cur_type, enum overload_flags flags)
{
  if (ctype && ctype != cur_type)
    {
      if (flags == DTOR_FLAG)
	error ("destructor for alien class %qT cannot be a member", ctype);
      else
	error ("constructor for alien class %qT cannot be a member", ctype);
      return 0;
    }
  return 1;
}
