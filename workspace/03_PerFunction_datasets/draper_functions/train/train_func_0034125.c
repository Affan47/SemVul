osd_uld_init(void)
{
	int err;

	err = class_register(&osd_uld_class);
	if (err) {
		OSD_ERR("Unable to register sysfs class => %d\n", err);
		return err;
	}

	err = register_chrdev_region(MKDEV(SCSI_OSD_MAJOR, 0),
				     SCSI_OSD_MAX_MINOR, osd_name);
	if (err) {
		OSD_ERR("Unable to register major %d for osd ULD => %d\n",
			SCSI_OSD_MAJOR, err);
		goto err_out;
	}

	err = scsi_register_driver(&osd_driver.gendrv);
	if (err) {
		OSD_ERR("scsi_register_driver failed => %d\n", err);
		goto err_out_chrdev;
	}

	OSD_INFO("LOADED %s\n", osd_version_string);
	return 0;

err_out_chrdev:
	unregister_chrdev_region(MKDEV(SCSI_OSD_MAJOR, 0), SCSI_OSD_MAX_MINOR);
err_out:
	class_unregister(&osd_uld_class);
	return err;
}
