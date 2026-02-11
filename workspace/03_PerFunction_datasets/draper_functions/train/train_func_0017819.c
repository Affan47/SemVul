lto_ft_decl_common (tree t)
{
  lto_ft_decl_minimal (t);
  LTO_FIXUP_TREE (DECL_SIZE (t));
  LTO_FIXUP_TREE (DECL_SIZE_UNIT (t));
  LTO_FIXUP_TREE (DECL_INITIAL (t));
  LTO_FIXUP_TREE (DECL_ATTRIBUTES (t));
  LTO_FIXUP_TREE (DECL_ABSTRACT_ORIGIN (t));
}
