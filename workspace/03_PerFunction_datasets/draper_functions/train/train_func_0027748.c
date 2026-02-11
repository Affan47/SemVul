format_2_instr(int opcode, symbol_ref_t *dest, expression_t *places,
	       symbol_ref_t *src, int ret)
{
	struct instruction *instr;
	struct ins_format2 *f2_instr;
	uint8_t shift_control;

	if (src->symbol == NULL)
		src = dest;


	test_writable_symbol(dest->symbol);
	test_readable_symbol(src->symbol);


	instr = seq_alloc();
	f2_instr = &instr->format.format2;
	f2_instr->ret = ret ? 1 : 0;
	f2_instr->opcode = AIC_OP_ROL;
	f2_instr->destination = dest->symbol->info.rinfo->address
			      + dest->offset;
	f2_instr->source = src->symbol->info.rinfo->address
			 + src->offset;
	if (places->value > 8 || places->value <= 0) {
		stop("illegal shift value", EX_DATAERR);

	}
	switch (opcode) {
	case AIC_OP_SHL:
		if (places->value == 8)
			shift_control = 0xf0;
		else
			shift_control = (places->value << 4) | places->value;
		break;
	case AIC_OP_SHR:
		if (places->value == 8) {
			shift_control = 0xf8;
		} else {
			shift_control = (places->value << 4)
				      | (8 - places->value)
				      | 0x08;
		}
		break;
	case AIC_OP_ROL:
		shift_control = places->value & 0x7;
		break;
	case AIC_OP_ROR:
		shift_control = (8 - places->value) | 0x08;
		break;
	default:
		shift_control = 0;
		stop("Invalid shift operation specified", EX_SOFTWARE);

		break;
	};
	f2_instr->shift_control = shift_control;
	symlist_free(&places->referenced_syms);
	instruction_ptr++;
}
