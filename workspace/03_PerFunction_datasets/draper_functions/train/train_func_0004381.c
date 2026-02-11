ahc_linux_register_host(struct ahc_softc *ahc, struct scsi_host_template *template)
{
	char	buf[80];
	struct	Scsi_Host *host;
	char	*new_name;
	u_long	s;
	int	retval;

	template->name = ahc->description;
	host = scsi_host_alloc(template, sizeof(struct ahc_softc *));
	if (host == NULL)
		return (ENOMEM);

	*((struct ahc_softc **)host->hostdata) = ahc;
	ahc->platform_data->host = host;
	host->can_queue = AHC_MAX_QUEUE;
	host->cmd_per_lun = 2;

	host->this_id = ahc->our_id;
	host->irq = ahc->platform_data->irq;
	host->max_id = (ahc->features & AHC_WIDE) ? 16 : 8;
	host->max_lun = AHC_NUM_LUNS;
	host->max_channel = (ahc->features & AHC_TWIN) ? 1 : 0;
	host->sg_tablesize = AHC_NSEG;
	ahc_lock(ahc, &s);
	ahc_set_unit(ahc, ahc_linux_unit++);
	ahc_unlock(ahc, &s);
	sprintf(buf, "scsi%d", host->host_no);
	new_name = kmalloc(strlen(buf) + 1, GFP_ATOMIC);
	if (new_name != NULL) {
		strcpy(new_name, buf);
		ahc_set_name(ahc, new_name);
	}
	host->unique_id = ahc->unit;
	ahc_linux_initialize_scsi_bus(ahc);
	ahc_intr_enable(ahc, TRUE);

	host->transportt = ahc_linux_transport_template;

	retval = scsi_add_host(host,
			(ahc->dev_softc ? &ahc->dev_softc->dev : NULL));
	if (retval) {
		printk(KERN_WARNING "aic7xxx: scsi_add_host failed\n");
		scsi_host_put(host);
		return retval;
	}

	scsi_scan_host(host);
	return 0;
}
