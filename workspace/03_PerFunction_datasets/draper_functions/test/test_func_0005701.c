arm_function_arg_boundary (enum machine_mode mode, const_tree type)
{
  return (ARM_DOUBLEWORD_ALIGN && arm_needs_doubleword_align (mode, type)
	  ? DOUBLEWORD_ALIGNMENT
	  : PARM_BOUNDARY);
}
