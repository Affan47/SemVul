default_builtin_support_vector_misalignment (enum machine_mode mode,
					     const_tree type
					     ATTRIBUTE_UNUSED,
					     int misalignment
					     ATTRIBUTE_UNUSED,
					     bool is_packed
					     ATTRIBUTE_UNUSED)
{
  if (optab_handler (movmisalign_optab, mode) != CODE_FOR_nothing)
    return true;
  return false;
}
