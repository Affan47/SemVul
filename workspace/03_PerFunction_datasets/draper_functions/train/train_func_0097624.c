local_define_builtin (const char *name, tree type, enum built_in_function code,
                      const char *library_name, int ecf_flags)
{
  tree decl;

  decl = add_builtin_function (name, type, code, BUILT_IN_NORMAL,
			       library_name, NULL_TREE);
  if (ecf_flags & ECF_CONST)
    TREE_READONLY (decl) = 1;
  if (ecf_flags & ECF_PURE)
    DECL_PURE_P (decl) = 1;
  if (ecf_flags & ECF_LOOPING_CONST_OR_PURE)
    DECL_LOOPING_CONST_OR_PURE_P (decl) = 1;
  if (ecf_flags & ECF_NORETURN)
    TREE_THIS_VOLATILE (decl) = 1;
  if (ecf_flags & ECF_NOTHROW)
    TREE_NOTHROW (decl) = 1;
  if (ecf_flags & ECF_MALLOC)
    DECL_IS_MALLOC (decl) = 1;
  if (ecf_flags & ECF_LEAF)
    DECL_ATTRIBUTES (decl) = tree_cons (get_identifier ("leaf"),
					NULL, DECL_ATTRIBUTES (decl));

  built_in_decls[code] = decl;
  implicit_built_in_decls[code] = decl;
}
