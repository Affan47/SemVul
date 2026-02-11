branchAddr(OPCODE *opcode, branch_enum_t branchtype, bool examine)
{
	Address *addr;
	x86dis_insn *o = (x86dis_insn*)opcode;
	assert(o->op[1].type == X86_OPTYPE_EMPTY);
	switch (o->op[0].type) {
		case X86_OPTYPE_IMM: {
			uint16 seg = 0;
			if (flags & ANALYX86DISASSEMBLER_FLAGS_SEGMENTED) {
				seg = getSegment(analy->addr);
			}
			addr = createAddress(seg, o->op[0].imm);
			return addr;
		}
		case X86_OPTYPE_FARPTR:
			if (flags & ANALYX86DISASSEMBLER_FLAGS_SEGMENTED) {
				addr = createAddress(o->op[0].farptr.seg, o->op[0].farptr.offset);
			} else {
				break;
			}
			return addr;
		case X86_OPTYPE_MEM: {
			taccess access;
			addr = NULL;
			if (o->op[0].mem.hasdisp) {
				addr = createAddress(0, o->op[0].mem.disp);
				access.type = acread;
				access.indexed = (o->op[0].mem.base != X86_REG_NO) || (o->op[0].mem.index != X86_REG_NO);
				access.size = o->op[0].size;
			} else {
				break;
			}
			if (examine && analy->validAddress(addr, scvalid)) {
				analy->dataAccess(addr, access);
				xref_enum_t xref;
				switch (branchtype) {
					case br_jXX:
					case br_jump:
						xref = xrefijump;
						break;
					case br_call:
						xref = xreficall;
						break;
					default: {assert(0);}
				}
				analy->addXRef(addr, analy->addr, xref);
			}
			if (examine) {
				delete addr;
				break;
			} else {
				return addr;
			}
		}
		default: break;
	}
	return new InvalidAddress();
}
