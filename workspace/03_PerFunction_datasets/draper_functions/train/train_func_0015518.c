tree_output_constant_def (tree exp)
{
  struct constant_descriptor_tree *desc, key;
  void **loc;
  tree decl;


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

  decl = SYMBOL_REF_DECL (XEXP (desc->rtl, 0));
  varpool_finalize_decl (decl);
  return decl;
}
