clone_die (dw_die_ref die)
{
  dw_die_ref clone;
  dw_attr_ref a;
  unsigned ix;

  clone = ggc_alloc_cleared_die_node ();
  clone->die_tag = die->die_tag;

  FOR_EACH_VEC_ELT (dw_attr_node, die->die_attr, ix, a)
    add_dwarf_attr (clone, a);

  return clone;
}
