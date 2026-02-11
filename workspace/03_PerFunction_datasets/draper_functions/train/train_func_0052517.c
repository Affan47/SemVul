compile_alternatives_z(assembly_operand switch_value, int n,
    int stack_level, int label, int flag)
{   switch(n)
    {   case 1:
            assemblez_2_branch(je_zc, switch_value,
                spec_stack[stack_level],
                label, flag); return;
        case 2:
            assemblez_3_branch(je_zc, switch_value,
                spec_stack[stack_level], spec_stack[stack_level+1],
                label, flag); return;
        case 3:
            assemblez_4_branch(je_zc, switch_value,
                spec_stack[stack_level], spec_stack[stack_level+1],
                spec_stack[stack_level+2],
                label, flag); return;
    }
}
