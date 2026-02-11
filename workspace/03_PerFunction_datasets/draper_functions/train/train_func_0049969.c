budget_patch_detach (struct saa7146_dev* dev)
{
	struct budget_patch *budget = (struct budget_patch*) dev->ext_priv;
	int err;

	if (budget->dvb_frontend) {
		dvb_unregister_frontend(budget->dvb_frontend);
		dvb_frontend_detach(budget->dvb_frontend);
	}
	err = ttpci_budget_deinit (budget);

	kfree (budget);

	return err;
}
