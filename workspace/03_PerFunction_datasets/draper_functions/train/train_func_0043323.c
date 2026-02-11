write_result_g(assembly_operand to, assembly_operand from)
{   if (to.value == from.value && to.type == from.type) return;
    assembleg_store(to, from);
}
