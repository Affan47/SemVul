lookup_constant_def (tree exp)
{
  struct constant_descriptor_tree *desc;
  struct constant_descriptor_tree key;

  key.value = exp;
  desc = htab_find (const_desc_htab, &key);

  return (desc ? desc->rtl : NULL_RTX);
}
