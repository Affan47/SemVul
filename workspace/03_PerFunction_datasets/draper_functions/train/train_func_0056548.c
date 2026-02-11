is_valid_ic(struct x86_ic *ic)
{
	if (*(((unsigned char *)ic->fn) - X86_CALL_DISP_OFFSET) != X86_CALL_OPC)
		return false;
	if (*(((unsigned char *)ic->imm) - X86_MOV_IMM_REG_IMM_OFFSET) != X86_MOV_EAX_OPC)
		return false;
	return true;
}
