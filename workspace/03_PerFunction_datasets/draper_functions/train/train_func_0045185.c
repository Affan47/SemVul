mono_decompose_vtype_opts_llvm (MonoCompile *cfg)
{
	MonoBasicBlock *bb, *first_bb;


	cfg->cbb = mono_mempool_alloc0 ((cfg)->mempool, sizeof (MonoBasicBlock));
	first_bb = cfg->cbb;

	for (bb = cfg->bb_entry; bb; bb = bb->next_bb) {
		MonoInst *ins;
		MonoInst *prev = NULL;
		MonoInst *src_var, *src, *dest;
		gboolean restart;
		int dreg;

		if (cfg->verbose_level > 2) mono_print_bb (bb, "BEFORE LOWER-VTYPE-OPTS(LLVM) ");

		cfg->cbb->code = cfg->cbb->last_ins = NULL;
		restart = TRUE;

		while (restart) {
			restart = FALSE;

			for (ins = bb->code; ins; ins = ins->next) {
				switch (ins->opcode) {
				case OP_STOREV_MEMBASE: {
					src_var = get_vreg_to_inst (cfg, ins->sreg1);

					if (!src_var) {
						g_assert (ins->klass);
						src_var = mono_compile_create_var_for_vreg (cfg, &ins->klass->byval_arg, OP_LOCAL, ins->sreg1);
					}

					EMIT_NEW_VARLOADA_VREG ((cfg), (src), ins->sreg1, &ins->klass->byval_arg);

					dreg = alloc_preg (cfg);
					EMIT_NEW_BIALU_IMM (cfg, dest, OP_ADD_IMM, dreg, ins->inst_destbasereg, ins->inst_offset);
					mini_emit_stobj (cfg, dest, src, src_var->klass, src_var->backend.is_pinvoke);
					break;
				}
				default:
					break;
				}

				g_assert (cfg->cbb == first_bb);

				if (cfg->cbb->code || (cfg->cbb != first_bb)) {


					mono_replace_ins (cfg, bb, ins, &prev, first_bb, cfg->cbb);
					first_bb->code = first_bb->last_ins = NULL;
					first_bb->in_count = first_bb->out_count = 0;
					cfg->cbb = first_bb;
				}
				else
					prev = ins;
			}
		}

		if (cfg->verbose_level > 2) mono_print_bb (bb, "AFTER LOWER-VTYPE-OPTS(LLVM) ");
	}
}
