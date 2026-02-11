implicitly_declare (functionid)
     tree functionid;
{
  tree decl;
  int traditional_warning = 0;

  int implicit_warning;


#if 0
  if (IDENTIFIER_IMPLICIT_DECL (functionid) != 0)
    decl = IDENTIFIER_IMPLICIT_DECL (functionid);
  else
#endif
    decl = build_decl (FUNCTION_DECL, functionid, default_function_type);


  if (TREE_PUBLIC (functionid) && IDENTIFIER_GLOBAL_VALUE (functionid) == 0)
    traditional_warning = 1;


  implicit_warning = (IDENTIFIER_IMPLICIT_DECL (functionid) == 0);

  DECL_EXTERNAL (decl) = 1;
  TREE_PUBLIC (decl) = 1;


  IDENTIFIER_IMPLICIT_DECL (functionid) = decl;


  pushdecl (decl);


  if (flag_objc)
    objc_check_decl (decl);

  rest_of_decl_compilation (decl, NULL, 0, 0);

  if (implicit_warning)
    implicit_decl_warning (functionid);
  else if (warn_traditional && traditional_warning)
    warning ("function `%s' was previously declared within a block",
	     IDENTIFIER_POINTER (functionid));


  gen_aux_info_record (decl, 0, 1, 0);


  decl_attributes (&decl, NULL_TREE, 0);

  return decl;
}
