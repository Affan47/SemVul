addr_to_parts (tree type, aff_tree *addr, tree iv_cand,
	       tree base_hint, struct mem_address *parts,
               bool speed)
{
  tree part;
  unsigned i;

  parts->symbol = NULL_TREE;
  parts->base = NULL_TREE;
  parts->index = NULL_TREE;
  parts->step = NULL_TREE;

  if (!addr->offset.is_zero ())
    parts->offset = double_int_to_tree (sizetype, addr->offset);
  else
    parts->offset = NULL_TREE;


  move_fixed_address_to_symbol (parts, addr);


  if (!base_hint && (addr->n > 2))
    move_variant_to_index (parts, addr, iv_cand);


  if (!parts->index)
    most_expensive_mult_to_index (type, parts, addr, speed);


  if (!parts->symbol && base_hint)
    move_hint_to_base (type, parts, base_hint, addr);
  if (!parts->symbol && !parts->base)
    move_pointer_to_base (parts, addr);


  for (i = 0; i < addr->n; i++)
    {
      part = fold_convert (sizetype, addr->elts[i].val);
      if (!addr->elts[i].coef.is_one ())
	part = fold_build2 (MULT_EXPR, sizetype, part,
			    double_int_to_tree (sizetype, addr->elts[i].coef));
      add_to_parts (parts, part);
    }
  if (addr->rest)
    add_to_parts (parts, fold_convert (sizetype, addr->rest));
}
