vm_interp_method_v(struct vm_method *method, va_list args, union jvalue *result)
{
	uint32_t pc;

	pc = 0;
	while (pc < method->code_attribute.code_length) {
		uint8_t opc = method->code_attribute.code[pc];

		if (interp(opc) == INTERP_RETURN)
			return;

		pc++;
	}
}
