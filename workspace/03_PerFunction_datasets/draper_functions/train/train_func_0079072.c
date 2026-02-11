reference_callee_copied (CUMULATIVE_ARGS *ca, enum machine_mode mode,
			 tree type, bool named_arg)
{
  if (type && TREE_ADDRESSABLE (type))
    return false;
  return targetm.calls.callee_copies (pack_cumulative_args (ca), mode, type,
				      named_arg);
}
