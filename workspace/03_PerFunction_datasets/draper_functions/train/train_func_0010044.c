ktd2692_remove(struct platform_device *pdev)
{
	struct ktd2692_context *led = platform_get_drvdata(pdev);
	int ret;

	led_classdev_flash_unregister(&led->fled_cdev);
	cancel_work_sync(&led->work_brightness_set);

	if (led->regulator) {
		ret = regulator_disable(led->regulator);
		if (ret)
			dev_err(&pdev->dev,
				"Failed to disable supply: %d\n", ret);
	}

	mutex_destroy(&led->lock);

	return 0;
}
