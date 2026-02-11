next_runtime_abi_02_receiver_is_class_object (tree receiver)
{
  if (TREE_CODE (receiver) == VAR_DECL
      && IS_CLASS (TREE_TYPE (receiver))
      && classrefs
      && VEC_length (ident_data_tuple, classrefs))
    {
      int count;
      ident_data_tuple *ref;

      FOR_EACH_VEC_ELT (ident_data_tuple, classrefs, count, ref)
	if (ref->data == receiver)
	  return ref->ident;
    }
  return NULL_TREE;
}
