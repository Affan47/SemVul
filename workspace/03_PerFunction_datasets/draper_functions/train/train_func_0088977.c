emit_dwarf_info (MonoAotCompile *acfg)
{
#ifdef EMIT_DWARF_INFO
	int i;
	char symbol2 [128];


	for (i = 0; i < acfg->nmethods; ++i) {
		MonoCompile *cfg = acfg->cfgs [i];

		if (!cfg)
			continue;


		if (cfg->compile_llvm)
			continue;

		sprintf (symbol2, "%sme_%x", acfg->temp_prefix, i);

		mono_dwarf_writer_emit_method (acfg->dwarf, cfg, cfg->method, cfg->asm_symbol, symbol2, cfg->jit_info->code_start, cfg->jit_info->code_size, cfg->args, cfg->locals, cfg->unwind_ops, mono_debug_find_method (cfg->jit_info->d.method, mono_domain_get ()));
	}
#endif
}
