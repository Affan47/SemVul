led_classdev_unregister(struct led_classdev *led_cdev)
{
#ifdef CONFIG_LEDS_TRIGGERS
	down_write(&led_cdev->trigger_lock);
	if (led_cdev->trigger)
		led_trigger_set(led_cdev, NULL);
	up_write(&led_cdev->trigger_lock);
#endif

	cancel_work_sync(&led_cdev->set_brightness_work);


	led_stop_software_blink(led_cdev);
	led_set_brightness(led_cdev, LED_OFF);

	device_unregister(led_cdev->dev);

	down_write(&leds_list_lock);
	list_del(&led_cdev->node);
	up_write(&leds_list_lock);

	mutex_destroy(&led_cdev->led_access);
}
