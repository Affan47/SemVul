mmc_sdio_pre_suspend(struct mmc_host *host)
{
	int i, err = 0;

	for (i = 0; i < host->card->sdio_funcs; i++) {
		struct sdio_func *func = host->card->sdio_func[i];
		if (func && sdio_func_present(func) && func->dev.driver) {
			const struct dev_pm_ops *pmops = func->dev.driver->pm;
			if (!pmops || !pmops->suspend || !pmops->resume) {

				err = -ENOSYS;
				break;
			}
		}
	}

	return err;
}
