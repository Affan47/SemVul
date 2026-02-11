bnx2fc_setup_task_ctx(struct bnx2fc_hba *hba)
{
	int rc = 0;
	struct regpair *task_ctx_bdt;
	dma_addr_t addr;
	int task_ctx_arr_sz;
	int i;


	hba->task_ctx_bd_tbl = dma_alloc_coherent(&hba->pcidev->dev,
						  PAGE_SIZE,
						  &hba->task_ctx_bd_dma,
						  GFP_KERNEL);
	if (!hba->task_ctx_bd_tbl) {
		printk(KERN_ERR PFX "unable to allocate task context BDT\n");
		rc = -1;
		goto out;
	}
	memset(hba->task_ctx_bd_tbl, 0, PAGE_SIZE);


	task_ctx_arr_sz = (hba->max_tasks / BNX2FC_TASKS_PER_PAGE);
	hba->task_ctx = kzalloc((task_ctx_arr_sz * sizeof(void *)),
				 GFP_KERNEL);
	if (!hba->task_ctx) {
		printk(KERN_ERR PFX "unable to allocate task context array\n");
		rc = -1;
		goto out1;
	}


	hba->task_ctx_dma = kmalloc((task_ctx_arr_sz *
					sizeof(dma_addr_t)), GFP_KERNEL);
	if (!hba->task_ctx_dma) {
		printk(KERN_ERR PFX "unable to alloc context mapping array\n");
		rc = -1;
		goto out2;
	}

	task_ctx_bdt = (struct regpair *)hba->task_ctx_bd_tbl;
	for (i = 0; i < task_ctx_arr_sz; i++) {

		hba->task_ctx[i] = dma_alloc_coherent(&hba->pcidev->dev,
						      PAGE_SIZE,
						      &hba->task_ctx_dma[i],
						      GFP_KERNEL);
		if (!hba->task_ctx[i]) {
			printk(KERN_ERR PFX "unable to alloc task context\n");
			rc = -1;
			goto out3;
		}
		memset(hba->task_ctx[i], 0, PAGE_SIZE);
		addr = (u64)hba->task_ctx_dma[i];
		task_ctx_bdt->hi = cpu_to_le32((u64)addr >> 32);
		task_ctx_bdt->lo = cpu_to_le32((u32)addr);
		task_ctx_bdt++;
	}
	return 0;

out3:
	for (i = 0; i < task_ctx_arr_sz; i++) {
		if (hba->task_ctx[i]) {

			dma_free_coherent(&hba->pcidev->dev, PAGE_SIZE,
				hba->task_ctx[i], hba->task_ctx_dma[i]);
			hba->task_ctx[i] = NULL;
		}
	}

	kfree(hba->task_ctx_dma);
	hba->task_ctx_dma = NULL;
out2:
	kfree(hba->task_ctx);
	hba->task_ctx = NULL;
out1:
	dma_free_coherent(&hba->pcidev->dev, PAGE_SIZE,
			hba->task_ctx_bd_tbl, hba->task_ctx_bd_dma);
	hba->task_ctx_bd_tbl = NULL;
out:
	return rc;
}
