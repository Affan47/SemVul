c_free_fixup(struct c_fixup *list, union c_insn *pc)
{
	struct c_fixup *current;

	while ((current = list)) {
		if (c_pass)
			current->pc->pc = pc;

		list = list->next;
		MEM_FREE(current);
	}
}
