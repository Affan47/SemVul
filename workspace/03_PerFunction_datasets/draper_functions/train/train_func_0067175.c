compile_alternatives(assembly_operand switch_value, int n,
    int stack_level, int label, int flag)
{
  if (!glulx_mode)
    compile_alternatives_z(switch_value, n, stack_level, label, flag);
  else
    compile_alternatives_g(switch_value, n, stack_level, label, flag);
}
