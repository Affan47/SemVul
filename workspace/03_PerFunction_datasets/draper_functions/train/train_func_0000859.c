pad_type_hash_eq (const void *p1, const void *p2)
{
  const struct pad_type_hash *const t1 = (const struct pad_type_hash *) p1;
  const struct pad_type_hash *const t2 = (const struct pad_type_hash *) p2;
  tree type1, type2;

  if (t1->hash != t2->hash)
    return 0;

  type1 = t1->type;
  type2 = t2->type;


  return
    TREE_TYPE (TYPE_FIELDS (type1)) == TREE_TYPE (TYPE_FIELDS (type2))
    && TYPE_SIZE (type1) == TYPE_SIZE (type2)
    && TYPE_ALIGN (type1) == TYPE_ALIGN (type2)
    && TYPE_ADA_SIZE (type1) == TYPE_ADA_SIZE (type2);
}
