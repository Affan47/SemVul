sym2_io_resume(struct pci_dev *pdev)
{
	struct Scsi_Host *shost = pci_get_drvdata(pdev);
	struct sym_data *sym_data = shost_priv(shost);

	spin_lock_irq(shost->host_lock);
	if (sym_data->io_reset)
		complete_all(sym_data->io_reset);
	spin_unlock_irq(shost->host_lock);
}
