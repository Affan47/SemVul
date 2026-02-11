qla24xx_disable_msix(struct qla_hw_data *ha)
{
	int i;
	struct qla_msix_entry *qentry;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	for (i = 0; i < ha->msix_count; i++) {
		qentry = &ha->msix_entries[i];
		if (qentry->have_irq) {

			irq_set_affinity_notifier(qentry->vector, NULL);
			free_irq(qentry->vector, qentry->rsp);
		}
	}
	pci_disable_msix(ha->pdev);
	kfree(ha->msix_entries);
	ha->msix_entries = NULL;
	ha->flags.msix_enabled = 0;
	ql_dbg(ql_dbg_init, vha, 0x0042,
	    "Disabled the MSI.\n");
}
