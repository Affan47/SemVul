def_builtin_1 (enum built_in_function fncode, const char *name,
	       enum built_in_class fnclass, tree fntype, tree libtype,
	       bool both_p, bool fallback_p, bool nonansi_p,
	       tree fnattrs, bool implicit_p)
{
  tree decl;
  const char *libname;

  if (fntype == error_mark_node)
    return;

  libname = name + strlen ("__builtin_");
  decl = add_builtin_function (name, fntype, fncode, fnclass,
			       (fallback_p ? libname : NULL),
			       fnattrs);

  if (both_p
      && !flag_no_builtin
      && !(nonansi_p && flag_no_nonansi_builtin))
    add_builtin_function (libname, libtype, fncode, fnclass,
			  NULL, fnattrs);

  built_in_decls[(int) fncode] = decl;
  if (implicit_p)
    implicit_built_in_decls[(int) fncode] = decl;
}
