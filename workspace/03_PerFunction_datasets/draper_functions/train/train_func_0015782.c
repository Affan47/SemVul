release_operand(struct operand *operand)
{
	if (operand_uses_reg(operand))
		list_del(&operand->reg.use_pos_list);

	if (operand_uses_index_reg(operand))
		list_del(&operand->index_reg.use_pos_list);
}
