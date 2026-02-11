is_mova() {
	if (!is_alu_inst())
		return false;
	alu_node *a = static_cast<alu_node*>(this);
	return (a->bc.op_ptr->flags & AF_MOVA);
}
