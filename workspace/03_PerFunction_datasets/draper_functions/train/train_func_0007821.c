mono_arch_get_llvm_imt_trampoline (MonoDomain *domain, MonoMethod *m, int vt_offset)
{
	guint8 *code, *start;
	int buf_len;
	int this_reg;

	buf_len = 32;

	start = code = mono_domain_code_reserve (domain, buf_len);

	this_reg = mono_arch_get_this_arg_reg (NULL);


	amd64_mov_reg_imm (code, MONO_ARCH_IMT_REG, m);

	amd64_mov_reg_membase (code, AMD64_RAX, this_reg, 0, 8);
	amd64_jump_membase (code, AMD64_RAX, vt_offset);
	amd64_ret (code);

	g_assert ((code - start) < buf_len);

	nacl_domain_code_validate (domain, &start, buf_len, &code);

	mono_arch_flush_icache (start, code - start);

	return start;
}
