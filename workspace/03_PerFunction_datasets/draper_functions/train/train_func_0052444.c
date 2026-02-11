may_propagate_copy_into_asm (tree dest)
{

  return !(TREE_CODE (dest) == SSA_NAME
	   && TREE_CODE (SSA_NAME_VAR (dest)) == VAR_DECL
	   && DECL_HARD_REGISTER (SSA_NAME_VAR (dest)));
}
