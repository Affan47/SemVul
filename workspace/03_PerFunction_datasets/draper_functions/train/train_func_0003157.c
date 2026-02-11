maybe_apply_pragma_weak (tree decl)
{
  tree id;
  int i;
  pending_weak *pe;


  if (vec_safe_is_empty (pending_weaks))
    return;


  if (!DECL_EXTERNAL (decl) && !TREE_PUBLIC (decl))
    return;


  if (TREE_CODE (decl) != FUNCTION_DECL && TREE_CODE (decl) != VAR_DECL)
    return;

  if (DECL_ASSEMBLER_NAME_SET_P (decl))
    id = DECL_ASSEMBLER_NAME (decl);
  else
    {
      id = DECL_ASSEMBLER_NAME (decl);
      SET_DECL_ASSEMBLER_NAME (decl, NULL_TREE);
    }

  FOR_EACH_VEC_ELT (*pending_weaks, i, pe)
    if (id == pe->name)
      {
	apply_pragma_weak (decl, pe->value);
	pending_weaks->unordered_remove (i);
	break;
      }
}
