cmc_instance_copy_from_base(CmdCfg *cmc, gpointer dst)
{
	if((cmc != NULL) && (dst != NULL))
		cmc_instance_copy(cmc, dst, cmc->base);
}
