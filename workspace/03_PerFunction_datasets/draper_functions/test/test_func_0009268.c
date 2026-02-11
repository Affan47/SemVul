get_vreg_from_var (MonoCompile *cfg, MonoInst *var)
{
	if (var->opcode == OP_REGVAR)

		return MONO_VARINFO (cfg, var->inst_c0)->vreg;
	else

		return var->dreg;
}
