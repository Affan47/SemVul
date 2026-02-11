hest_ghes_dev_register(unsigned int ghes_count)
{
	int rc, i;
	struct ghes_arr ghes_arr;

	ghes_arr.count = 0;
	ghes_arr.ghes_devs = kmalloc(sizeof(void *) * ghes_count, GFP_KERNEL);
	if (!ghes_arr.ghes_devs)
		return -ENOMEM;

	rc = apei_hest_parse(hest_parse_ghes, &ghes_arr);
	if (rc)
		goto err;
out:
	kfree(ghes_arr.ghes_devs);
	return rc;
err:
	for (i = 0; i < ghes_arr.count; i++)
		platform_device_unregister(ghes_arr.ghes_devs[i]);
	goto out;
}
