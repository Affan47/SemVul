ata_acpi_on_devcfg(struct ata_device *dev)
{
	struct ata_port *ap = dev->link->ap;
	struct ata_eh_context *ehc = &ap->link.eh_context;
	int acpi_sata = ap->flags & ATA_FLAG_ACPI_SATA;
	int nr_executed = 0;
	int rc;

	if (!ata_dev_acpi_handle(dev))
		return 0;


	if (!(dev->flags & ATA_DFLAG_ACPI_PENDING) &&
	    !(acpi_sata && (ehc->i.flags & ATA_EHI_DID_HARDRESET)))
		return 0;


	if (acpi_sata) {
		rc = ata_acpi_push_id(dev);
		if (rc && rc != -ENOENT)
			goto acpi_err;
	}


	rc = ata_acpi_exec_tfs(dev, &nr_executed);
	if (rc)
		goto acpi_err;

	dev->flags &= ~ATA_DFLAG_ACPI_PENDING;


	if (nr_executed) {
		rc = ata_dev_reread_id(dev, 0);
		if (rc < 0) {
			ata_dev_err(dev,
				    "failed to IDENTIFY after ACPI commands\n");
			return rc;
		}
	}

	return 0;

 acpi_err:

	if (rc == -EINVAL && !nr_executed && !(ap->pflags & ATA_PFLAG_FROZEN))
		return 0;


	if (!(dev->flags & ATA_DFLAG_ACPI_FAILED)) {
		dev->flags |= ATA_DFLAG_ACPI_FAILED;
		return rc;
	}

	dev->flags |= ATA_DFLAG_ACPI_DISABLED;
	ata_dev_warn(dev, "ACPI: failed the second time, disabled\n");


	if (!nr_executed && !(ap->pflags & ATA_PFLAG_FROZEN))
		return 0;

	return rc;
}
