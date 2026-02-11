remove_AT (dw_die_ref die, enum dwarf_attribute attr_kind)
{
  dw_attr_ref a;
  unsigned ix;

  if (! die)
    return;

  FOR_EACH_VEC_ELT (dw_attr_node, die->die_attr, ix, a)
    if (a->dw_attr == attr_kind)
      {
	if (AT_class (a) == dw_val_class_str)
	  if (a->dw_attr_val.v.val_str->refcount)
	    a->dw_attr_val.v.val_str->refcount--;


	VEC_ordered_remove (dw_attr_node, die->die_attr, ix);
	return;
      }
}
