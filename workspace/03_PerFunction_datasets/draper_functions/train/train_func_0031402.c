ahd_linux_pci_dev_remove(struct pci_dev *pdev)
{
	struct ahd_softc *ahd = pci_get_drvdata(pdev);
	u_long s;

	if (ahd->platform_data && ahd->platform_data->host)
			scsi_remove_host(ahd->platform_data->host);

	ahd_lock(ahd, &s);
	ahd_intr_enable(ahd, FALSE);
	ahd_unlock(ahd, &s);
	ahd_free(ahd);
}
