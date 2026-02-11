skl_free_dsp(struct skl *skl)
{
	struct hdac_ext_bus *ebus = &skl->ebus;
	struct hdac_bus *bus = ebus_to_hbus(ebus);
	struct skl_sst *ctx =  skl->skl_sst;


	snd_hdac_ext_bus_ppcap_int_enable(&skl->ebus, false);

	skl_sst_dsp_cleanup(bus->dev, ctx);
	if (ctx->dsp->addr.lpe)
		iounmap(ctx->dsp->addr.lpe);
}
