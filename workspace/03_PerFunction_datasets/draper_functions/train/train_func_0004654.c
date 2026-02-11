calculate_direct_bases (tree type)
{
  VEC(tree, gc) *vector = make_tree_vector();
  tree bases_vec = NULL_TREE;
  VEC(tree, none) *base_binfos;
  tree binfo;
  unsigned i;

  complete_type (type);

  if (!NON_UNION_CLASS_TYPE_P (type))
    return make_tree_vec (0);

  base_binfos = BINFO_BASE_BINFOS (TYPE_BINFO (type));


  for (i = 0; VEC_iterate (tree, base_binfos, i, binfo); i++)
    {
      if (BINFO_VIRTUAL_P (binfo))
       {
         VEC_safe_push (tree, gc, vector, binfo);
       }
    }


  for (i = 0; VEC_iterate (tree, base_binfos, i, binfo); i++)
    {
      if (!BINFO_VIRTUAL_P (binfo))
       {
         VEC_safe_push (tree, gc, vector, binfo);
       }
    }


  bases_vec = make_tree_vec (VEC_length (tree, vector));

  for (i = 0; i < VEC_length (tree, vector); ++i)
    {
      TREE_VEC_ELT (bases_vec, i) = BINFO_TYPE (VEC_index (tree, vector, i));
    }
  return bases_vec;
}
