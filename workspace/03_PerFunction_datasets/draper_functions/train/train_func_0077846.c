asm_visit_addr (gimple stmt ATTRIBUTE_UNUSED, tree op,
		void *data ATTRIBUTE_UNUSED)
{
  op = get_base_address (op);
  if (op
      && DECL_P (op))
    disqualify_candidate (op, "Non-scalarizable GIMPLE_ASM operand.");

  return false;
}
