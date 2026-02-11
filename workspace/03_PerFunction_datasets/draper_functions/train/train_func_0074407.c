wil_pmc_free(struct wil6210_priv *wil, int send_pmc_cmd)
{
	struct pmc_ctx *pmc = &wil->pmc;
	struct device *dev = wil_to_dev(wil);
	struct wmi_pmc_cmd pmc_cmd = {0};

	mutex_lock(&pmc->lock);

	pmc->last_cmd_status = 0;

	if (!wil_is_pmc_allocated(pmc)) {
		wil_dbg_misc(wil, "%s: Error, can't free - not allocated\n",
			     __func__);
		pmc->last_cmd_status = -EPERM;
		mutex_unlock(&pmc->lock);
		return;
	}

	if (send_pmc_cmd) {
		wil_dbg_misc(wil, "%s: send WMI_PMC_CMD with RELEASE op\n",
			     __func__);
		pmc_cmd.op = WMI_PMC_RELEASE;
		pmc->last_cmd_status =
				wmi_send(wil, WMI_PMC_CMDID, &pmc_cmd,
					 sizeof(pmc_cmd));
		if (pmc->last_cmd_status) {
			wil_err(wil,
				"%s WMI_PMC_CMD with RELEASE op failed, status %d",
				__func__, pmc->last_cmd_status);


		}
	}

	if (pmc->pring_va) {
		size_t buf_size = sizeof(struct vring_tx_desc) *
				  pmc->num_descriptors;

		wil_dbg_misc(wil, "%s: free pring va %p\n",
			     __func__, pmc->pring_va);
		dma_free_coherent(dev, buf_size, pmc->pring_va, pmc->pring_pa);

		pmc->pring_va = NULL;
	} else {
		pmc->last_cmd_status = -ENOENT;
	}

	if (pmc->descriptors) {
		int i;

		for (i = 0;
		     pmc->descriptors[i].va && i < pmc->num_descriptors; i++) {
			dma_free_coherent(dev,
					  pmc->descriptor_size,
					  pmc->descriptors[i].va,
					  pmc->descriptors[i].pa);
			pmc->descriptors[i].va = NULL;
		}
		wil_dbg_misc(wil, "%s: free descriptor info %d/%d\n",
			     __func__, i, pmc->num_descriptors);
		wil_dbg_misc(wil,
			     "%s: free pmc descriptors info list %p\n",
			     __func__, pmc->descriptors);
		kfree(pmc->descriptors);
		pmc->descriptors = NULL;
	} else {
		pmc->last_cmd_status = -ENOENT;
	}

	mutex_unlock(&pmc->lock);
}
