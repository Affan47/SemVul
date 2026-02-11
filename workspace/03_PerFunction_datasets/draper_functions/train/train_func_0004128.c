gimple_build_asm_vec (const char *string, VEC(tree,gc)* inputs,
                      VEC(tree,gc)* outputs, VEC(tree,gc)* clobbers,
		      VEC(tree,gc)* labels)
{
  gimple p;
  unsigned i;

  p = gimple_build_asm_1 (string,
                          VEC_length (tree, inputs),
                          VEC_length (tree, outputs),
                          VEC_length (tree, clobbers),
			  VEC_length (tree, labels));

  for (i = 0; i < VEC_length (tree, inputs); i++)
    gimple_asm_set_input_op (p, i, VEC_index (tree, inputs, i));

  for (i = 0; i < VEC_length (tree, outputs); i++)
    gimple_asm_set_output_op (p, i, VEC_index (tree, outputs, i));

  for (i = 0; i < VEC_length (tree, clobbers); i++)
    gimple_asm_set_clobber_op (p, i, VEC_index (tree, clobbers, i));

  for (i = 0; i < VEC_length (tree, labels); i++)
    gimple_asm_set_label_op (p, i, VEC_index (tree, labels, i));

  return p;
}
