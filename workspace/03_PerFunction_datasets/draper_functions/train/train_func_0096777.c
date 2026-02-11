skx_register_mci(struct skx_imc *imc)
{
	struct mem_ctl_info *mci;
	struct edac_mc_layer layers[2];
	struct pci_dev *pdev = imc->chan[0].cdev;
	struct skx_pvt *pvt;
	int rc;


	layers[0].type = EDAC_MC_LAYER_CHANNEL;
	layers[0].size = NUM_CHANNELS;
	layers[0].is_virt_csrow = false;
	layers[1].type = EDAC_MC_LAYER_SLOT;
	layers[1].size = NUM_DIMMS;
	layers[1].is_virt_csrow = true;
	mci = edac_mc_alloc(imc->mc, ARRAY_SIZE(layers), layers,
			    sizeof(struct skx_pvt));

	if (unlikely(!mci))
		return -ENOMEM;

	edac_dbg(0, "MC#%d: mci = %p\n", imc->mc, mci);


	imc->mci = mci;
	pvt = mci->pvt_info;
	pvt->imc = imc;

	mci->ctl_name = kasprintf(GFP_KERNEL, "Skylake Socket#%d IMC#%d",
				  imc->node_id, imc->lmc);
	mci->mtype_cap = MEM_FLAG_DDR4;
	mci->edac_ctl_cap = EDAC_FLAG_NONE;
	mci->edac_cap = EDAC_FLAG_NONE;
	mci->mod_name = "skx_edac.c";
	mci->dev_name = pci_name(imc->chan[0].cdev);
	mci->mod_ver = SKX_REVISION;
	mci->ctl_page_to_phys = NULL;

	rc = skx_get_dimm_config(mci);
	if (rc < 0)
		goto fail;


	mci->pdev = &pdev->dev;


	if (unlikely(edac_mc_add_mc(mci))) {
		edac_dbg(0, "MC: failed edac_mc_add_mc()\n");
		rc = -EINVAL;
		goto fail;
	}

	return 0;

fail:
	kfree(mci->ctl_name);
	edac_mc_free(mci);
	imc->mci = NULL;
	return rc;
}
