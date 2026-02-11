BasicBlock_opcode(kBasicBlock *bb)
{
	if(DP(bb)->size == 0) return OPCODE_NOP;
	return DP(bb)->opbuf->opcode;
}
