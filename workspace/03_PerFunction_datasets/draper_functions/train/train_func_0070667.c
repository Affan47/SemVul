sm501_create_subdev(struct sm501_devdata *sm, char *name,
		    unsigned int res_count, unsigned int platform_data_size)
{
	struct sm501_device *smdev;

	smdev = kzalloc(sizeof(struct sm501_device) +
			(sizeof(struct resource) * res_count) +
			platform_data_size, GFP_KERNEL);
	if (!smdev)
		return NULL;

	smdev->pdev.dev.release = sm501_device_release;

	smdev->pdev.name = name;
	smdev->pdev.id = sm->pdev_id;
	smdev->pdev.dev.parent = sm->dev;

	if (res_count) {
		smdev->pdev.resource = (struct resource *)(smdev+1);
		smdev->pdev.num_resources = res_count;
	}
	if (platform_data_size)
		smdev->pdev.dev.platform_data = (void *)(smdev+1);

	return &smdev->pdev;
}
