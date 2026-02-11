build_this_parm (tree type, cp_cv_quals quals)
{
  tree this_type;
  tree qual_type;
  tree parm;
  cp_cv_quals this_quals;

  if (CLASS_TYPE_P (type))
    {
      this_type
	= cp_build_qualified_type (type, quals & ~TYPE_QUAL_RESTRICT);
      this_type = build_pointer_type (this_type);
    }
  else
    this_type = type_of_this_parm (type);


  this_quals = (quals & TYPE_QUAL_RESTRICT) | TYPE_QUAL_CONST;
  qual_type = cp_build_qualified_type (this_type, this_quals);
  parm = build_artificial_parm (this_identifier, qual_type);
  cp_apply_type_quals_to_decl (this_quals, parm);
  return parm;
}
