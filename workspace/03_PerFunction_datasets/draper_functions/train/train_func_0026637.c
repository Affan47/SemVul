beiscsi_free_mem(struct beiscsi_hba *phba)
{
	struct be_mem_descriptor *mem_descr;
	int i, j;

	mem_descr = phba->init_mem;
	i = 0;
	j = 0;
	for (i = 0; i < SE_MEM_MAX; i++) {
		for (j = mem_descr->num_elements; j > 0; j--) {
			pci_free_consistent(phba->pcidev,
			  mem_descr->mem_array[j - 1].size,
			  mem_descr->mem_array[j - 1].virtual_address,
			  (unsigned long)mem_descr->mem_array[j - 1].
			  bus_address.u.a64.address);
		}

		kfree(mem_descr->mem_array);
		mem_descr++;
	}
	kfree(phba->init_mem);
	kfree(phba->phwi_ctrlr->wrb_context);
	kfree(phba->phwi_ctrlr);
}
