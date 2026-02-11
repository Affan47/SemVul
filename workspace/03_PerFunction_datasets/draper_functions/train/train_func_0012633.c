get_opcode_name(enum opcode op) {
	int i;

	for (i = 0; i < sizeof(opcode_info) / sizeof(opcode_info[0]); i++)
		if (op == opcode_info[i].op)
			return opcode_info[i].name;
	assert(0);
	return NULL;
}
