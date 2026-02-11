load_simd_vreg (MonoCompile *cfg, MonoMethod *cmethod, MonoInst *src, gboolean *indirect)
{
	if (indirect)
		*indirect = FALSE;
	if (src->opcode == OP_XMOVE) {
		return src->sreg1;
	} else if (src->opcode == OP_LDADDR) {
		int res = ((MonoInst*)src->inst_p0)->dreg;
		NULLIFY_INS (src);
		return res;
	} else if (src->type == STACK_VTYPE) {
		return src->dreg;
	} else if (src->type == STACK_PTR || src->type == STACK_MP) {
		MonoInst *ins;
		if (indirect)
			*indirect = TRUE;

		MONO_INST_NEW (cfg, ins, OP_LOADX_MEMBASE);
		ins->klass = cmethod->klass;
		ins->sreg1 = src->dreg;
		ins->type = STACK_VTYPE;
		ins->dreg = alloc_ireg (cfg);
		MONO_ADD_INS (cfg->cbb, ins);
		return ins->dreg;
	}
	g_warning ("load_simd_vreg:: could not infer source simd (%d) vreg for op", src->type);
	mono_print_ins (src);
	g_assert_not_reached ();
}
