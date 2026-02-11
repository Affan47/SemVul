fbtft_sysfs_exit(struct fbtft_par *par)
{
	device_remove_file(par->info->dev, &debug_device_attr);
	if (par->gamma.curves && par->fbtftops.set_gamma)
		device_remove_file(par->info->dev, &gamma_device_attrs[0]);
}
