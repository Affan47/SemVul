beiscsi_msix_enable(struct beiscsi_hba *phba)
{
	int i, status;

	for (i = 0; i <= phba->num_cpus; i++)
		phba->msix_entries[i].entry = i;

	status = pci_enable_msix_range(phba->pcidev, phba->msix_entries,
				       phba->num_cpus + 1, phba->num_cpus + 1);
	if (status > 0)
		phba->msix_enabled = true;

	return;
}
