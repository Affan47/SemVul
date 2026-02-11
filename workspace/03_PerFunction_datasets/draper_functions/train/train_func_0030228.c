adp5520_led_remove(struct platform_device *pdev)
{
	struct adp5520_leds_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct adp5520_led *led;
	int i;

	led = platform_get_drvdata(pdev);

	adp5520_clr_bits(led->master, ADP5520_LED_CONTROL,
		 ADP5520_LED1_EN | ADP5520_LED2_EN | ADP5520_LED3_EN);

	for (i = 0; i < pdata->num_leds; i++) {
		led_classdev_unregister(&led[i].cdev);
		cancel_work_sync(&led[i].work);
	}

	return 0;
}
