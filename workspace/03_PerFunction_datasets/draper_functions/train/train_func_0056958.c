rc_print_presub_instruction(FILE * f,
					struct rc_presub_instruction inst)
{
	fprintf(f,"(");
	switch(inst.Opcode){
	case RC_PRESUB_BIAS:
		fprintf(f, "1 - 2 * ");
		rc_print_register(f, inst.SrcReg[0].File,
				inst.SrcReg[0].Index,inst.SrcReg[0].RelAddr);
		break;
	case RC_PRESUB_SUB:
		rc_print_register(f, inst.SrcReg[1].File,
				inst.SrcReg[1].Index,inst.SrcReg[1].RelAddr);
		fprintf(f, " - ");
		rc_print_register(f, inst.SrcReg[0].File,
				inst.SrcReg[0].Index,inst.SrcReg[0].RelAddr);
		break;
	case RC_PRESUB_ADD:
		rc_print_register(f, inst.SrcReg[1].File,
				inst.SrcReg[1].Index,inst.SrcReg[1].RelAddr);
		fprintf(f, " + ");
		rc_print_register(f, inst.SrcReg[0].File,
				inst.SrcReg[0].Index,inst.SrcReg[0].RelAddr);
		break;
	case RC_PRESUB_INV:
		fprintf(f, "1 - ");
		rc_print_register(f, inst.SrcReg[0].File,
				inst.SrcReg[0].Index,inst.SrcReg[0].RelAddr);
		break;
	default:
		break;
	}
	fprintf(f, ")");
}
