execute_at(struct at_type *at_ptr)
{
    int instruction_index, operator, count;
    int saved_jump_offset = jump_offset;

    count = at_ptr->a_count;
    for (instruction_index = 0; instruction_index < count;) {
	operator = (int) at_ptr->actions[instruction_index].index;
	jump_offset = 1;
	(*ft[operator].func) (&(at_ptr->actions[instruction_index].arg));
	assert(is_jump(operator) || (jump_offset == 1));
	instruction_index += jump_offset;
    }

    jump_offset = saved_jump_offset;
}
