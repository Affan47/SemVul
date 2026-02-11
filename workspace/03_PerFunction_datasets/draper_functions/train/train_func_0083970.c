simd_intrinsic_emit_long_getter (const SimdIntrinsc *intrinsic, MonoCompile *cfg, MonoMethod *cmethod, MonoInst **args)
{
	MonoInst *ins;
	int vreg;
	gboolean is_r8 = mono_method_signature (cmethod)->ret->type == MONO_TYPE_R8;

	vreg = load_simd_vreg (cfg, cmethod, args [0], NULL);

	MONO_INST_NEW (cfg, ins, is_r8 ? OP_EXTRACT_R8 : OP_EXTRACT_I8);
	ins->klass = cmethod->klass;
	ins->sreg1 = vreg;
	ins->inst_c0 = intrinsic->opcode;
	if (is_r8) {
		ins->type = STACK_R8;
		ins->dreg = alloc_freg (cfg);
		ins->backend.spill_var = get_double_spill_area (cfg);
	} else {
		ins->type = STACK_I8;
		ins->dreg = alloc_lreg (cfg);
	}
	MONO_ADD_INS (cfg->cbb, ins);

	return ins;
}
