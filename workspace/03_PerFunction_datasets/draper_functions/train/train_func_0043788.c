rarvm_optimize(struct rarvm_prepared_program *prg)
{
	struct rarvm_prepared_command *code, *cmd;
	int code_size, i, flags_required, j, flags;

	code = prg->cmd.array;
	code_size = prg->cmd_count;

	for (i=0 ; i < code_size ; i++) {
		cmd = &code[i];
		switch(cmd->op_code) {
			case VM_MOV:
				cmd->op_code = cmd->byte_mode ? VM_MOVB:VM_MOVD;
				continue;
			case VM_CMP:
				cmd->op_code = cmd->byte_mode ? VM_CMPB:VM_CMPD;
				continue;
			default:
				break;
		}
		if ((vm_cmdflags[cmd->op_code] & VMCF_CHFLAGS) == 0) {
			continue;
		}
		flags_required = FALSE;
		for (j=i+1 ; j < code_size ; j++) {
			flags = vm_cmdflags[code[j].op_code];
			if (flags & (VMCF_JUMP|VMCF_PROC|VMCF_USEFLAGS)) {
				flags_required=TRUE;
				break;
			}
			if (flags & VMCF_CHFLAGS) {
				break;
			}
		}
		if (flags_required) {
			continue;
		}
		switch(cmd->op_code) {
			case VM_ADD:
				cmd->op_code = cmd->byte_mode ? VM_ADDB:VM_ADDD;
				continue;
			case VM_SUB:
				cmd->op_code = cmd->byte_mode ? VM_SUBB:VM_SUBD;
				continue;
			case VM_INC:
				cmd->op_code = cmd->byte_mode ? VM_INCB:VM_INCD;
				continue;
			case VM_DEC:
				cmd->op_code = cmd->byte_mode ? VM_DECB:VM_DECD;
				continue;
			case VM_NEG:
				cmd->op_code = cmd->byte_mode ? VM_NEGB:VM_NEGD;
				continue;
			default:
				break;
		}
	}
}
