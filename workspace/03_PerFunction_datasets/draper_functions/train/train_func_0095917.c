mv_platform_resume(struct platform_device *pdev)
{
	struct ata_host *host = platform_get_drvdata(pdev);
	const struct mbus_dram_target_info *dram;
	int ret;

	if (host) {
		struct mv_host_priv *hpriv = host->private_data;


		dram = mv_mbus_dram_info();
		if (dram)
			mv_conf_mbus_windows(hpriv, dram);


		ret = mv_init_host(host);
		if (ret) {
			printk(KERN_ERR DRV_NAME ": Error during HW init\n");
			return ret;
		}
		ata_host_resume(host);
	}

	return 0;
}
