OPCODE_fmn(kmethodn_t mn, int diff)
{
	switch(mn) {
	case MN_opNEG: return OPCODE_fNEG;
	case MN_opADD: return OPCODE_fADD + diff;
	case MN_opSUB: return OPCODE_fSUB + diff;
	case MN_opMUL: return OPCODE_fMUL + diff;
	case MN_opDIV: return OPCODE_fDIV + diff;
	case MN_opEQ:  return OPCODE_fEQ + diff;
	case MN_opNOTEQ: return OPCODE_fNEQ + diff;
	case MN_opLT:  return OPCODE_fLT + diff;
	case MN_opLTE: return OPCODE_fLTE + diff;
	case MN_opGT:  return OPCODE_fGT + diff;
	case MN_opGTE: return OPCODE_fGTE + diff;
	}
	return OPCODE_NOP;
}
