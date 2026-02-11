build_array_declarator (expr, quals, static_p, vla_unspec_p)
     tree expr;
     tree quals;
     int static_p;
     int vla_unspec_p;
{
  tree decl;
  decl = build_nt (ARRAY_REF, NULL_TREE, expr);
  TREE_TYPE (decl) = quals;
  TREE_STATIC (decl) = (static_p ? 1 : 0);
  if (pedantic && !flag_isoc99)
    {
      if (static_p || quals != NULL_TREE)
	pedwarn ("ISO C90 does not support `static' or type qualifiers in parameter array declarators");
      if (vla_unspec_p)
	pedwarn ("ISO C90 does not support `[*]' array declarators");
    }
  if (vla_unspec_p)
    warning ("GCC does not yet properly implement `[*]' array declarators");
  return decl;
}
