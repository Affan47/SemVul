qla24xx_reset_chip(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;

	if (pci_channel_offline(ha->pdev) &&
	    ha->flags.pci_channel_io_perm_failure) {
		return;
	}

	ha->isp_ops->disable_intrs(ha);

	qla25xx_manipulate_risc_semaphore(vha);


	qla24xx_reset_risc(vha);
}
