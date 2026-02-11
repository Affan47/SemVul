mono_create_tls_get_offset (MonoCompile *cfg, int offset)
{
	MonoInst* ins;

	if (!cfg->backend->have_tls_get)
		return NULL;

	if (offset == -1)
		return NULL;

	MONO_INST_NEW (cfg, ins, OP_TLS_GET);
	ins->dreg = mono_alloc_preg (cfg);
	ins->inst_offset = offset;
	return ins;
}
