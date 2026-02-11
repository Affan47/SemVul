x86_oplist_append( x86_insn_t *insn, x86_oplist_t *op ) {
	x86_oplist_t *list;

	if (! insn ) {
		return;
	}

	list = insn->operands;
	if (! list ) {
		insn->operand_count = 1;


		insn->explicit_count = 1;
		insn->operands = op;
		return;
	}


	for ( ; list->next; list = list->next )
		;

	insn->operand_count = insn->operand_count + 1;
	insn->explicit_count = insn->explicit_count + 1;
	list->next = op;

	return;
}
