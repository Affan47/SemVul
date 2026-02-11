amodule_contains_code_addr (MonoAotModule *amodule, guint8 *code)
{
	return (code >= amodule->jit_code_start && code <= amodule->jit_code_end) ||
		(code >= amodule->llvm_code_start && code <= amodule->llvm_code_end);
}
