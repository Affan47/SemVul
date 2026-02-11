cfspi_init_module(void)
{
	int result;


	spin_lock_init(&cfspi_list_lock);


	result = platform_driver_register(&cfspi_spi_driver);
	if (result) {
		printk(KERN_ERR "Could not register platform SPI driver.\n");
		goto err_dev_register;
	}


	result =
	    driver_create_file(&cfspi_spi_driver.driver,
			       &driver_attr_up_head_align);
	if (result) {
		printk(KERN_ERR "Sysfs creation failed 1.\n");
		goto err_create_up_head_align;
	}

	result =
	    driver_create_file(&cfspi_spi_driver.driver,
			       &driver_attr_up_tail_align);
	if (result) {
		printk(KERN_ERR "Sysfs creation failed 2.\n");
		goto err_create_up_tail_align;
	}

	result =
	    driver_create_file(&cfspi_spi_driver.driver,
			       &driver_attr_down_head_align);
	if (result) {
		printk(KERN_ERR "Sysfs creation failed 3.\n");
		goto err_create_down_head_align;
	}

	result =
	    driver_create_file(&cfspi_spi_driver.driver,
			       &driver_attr_down_tail_align);
	if (result) {
		printk(KERN_ERR "Sysfs creation failed 4.\n");
		goto err_create_down_tail_align;
	}

	result =
	    driver_create_file(&cfspi_spi_driver.driver,
			       &driver_attr_frame_align);
	if (result) {
		printk(KERN_ERR "Sysfs creation failed 5.\n");
		goto err_create_frame_align;
	}
	driver_debugfs_create();
	return result;

 err_create_frame_align:
	driver_remove_file(&cfspi_spi_driver.driver,
			   &driver_attr_down_tail_align);
 err_create_down_tail_align:
	driver_remove_file(&cfspi_spi_driver.driver,
			   &driver_attr_down_head_align);
 err_create_down_head_align:
	driver_remove_file(&cfspi_spi_driver.driver,
			   &driver_attr_up_tail_align);
 err_create_up_tail_align:
	driver_remove_file(&cfspi_spi_driver.driver,
			   &driver_attr_up_head_align);
 err_create_up_head_align:
	platform_driver_unregister(&cfspi_spi_driver);
 err_dev_register:
	return result;
}
