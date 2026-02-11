snic_request_intr(struct snic *snic)
{
	int ret = 0, i;
	enum vnic_dev_intr_mode intr_mode;

	intr_mode = svnic_dev_get_intr_mode(snic->vdev);
	SNIC_BUG_ON(intr_mode != VNIC_DEV_INTR_MODE_MSIX);


	sprintf(snic->msix[SNIC_MSIX_WQ].devname,
		"%.11s-scsi-wq",
		snic->name);
	snic->msix[SNIC_MSIX_WQ].isr = snic_isr_msix_wq;
	snic->msix[SNIC_MSIX_WQ].devid = snic;

	sprintf(snic->msix[SNIC_MSIX_IO_CMPL].devname,
		"%.11s-io-cmpl",
		snic->name);
	snic->msix[SNIC_MSIX_IO_CMPL].isr = snic_isr_msix_io_cmpl;
	snic->msix[SNIC_MSIX_IO_CMPL].devid = snic;

	sprintf(snic->msix[SNIC_MSIX_ERR_NOTIFY].devname,
		"%.11s-err-notify",
		snic->name);
	snic->msix[SNIC_MSIX_ERR_NOTIFY].isr = snic_isr_msix_err_notify;
	snic->msix[SNIC_MSIX_ERR_NOTIFY].devid = snic;

	for (i = 0; i < ARRAY_SIZE(snic->msix); i++) {
		ret = request_irq(snic->msix_entry[i].vector,
				  snic->msix[i].isr,
				  0,
				  snic->msix[i].devname,
				  snic->msix[i].devid);
		if (ret) {
			SNIC_HOST_ERR(snic->shost,
				      "MSI-X: requrest_irq(%d) failed %d\n",
				      i,
				      ret);
			snic_free_intr(snic);
			break;
		}
		snic->msix[i].requested = 1;
	}

	return ret;
}
