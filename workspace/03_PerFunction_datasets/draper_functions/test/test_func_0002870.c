skd_free_skcomp(struct skd_device *skdev)
{
	if (skdev->skcomp_table != NULL) {
		u32 nbytes;

		nbytes = sizeof(skdev->skcomp_table[0]) *
			 SKD_N_COMPLETION_ENTRY;
		pci_free_consistent(skdev->pdev, nbytes,
				    skdev->skcomp_table, skdev->cq_dma_address);
	}

	skdev->skcomp_table = NULL;
	skdev->cq_dma_address = 0;
}
