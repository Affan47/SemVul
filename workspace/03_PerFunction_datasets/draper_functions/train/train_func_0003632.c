output_constant_def (tree exp, int defer)
{
  struct constant_descriptor_tree *desc;
  struct constant_descriptor_tree key;
  void **loc;


  key.value = exp;
  key.hash = const_hash_1 (exp);
  loc = htab_find_slot_with_hash (const_desc_htab, &key, key.hash, INSERT);

  desc = (struct constant_descriptor_tree *) *loc;
  if (desc == 0)
    {
      desc = build_constant_desc (exp);
      desc->hash = key.hash;
      *loc = desc;
    }

  maybe_output_constant_def_contents (desc, defer);
  return desc->rtl;
}
