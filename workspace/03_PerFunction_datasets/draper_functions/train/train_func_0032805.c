iwl_led_brightness_set(struct led_classdev *led_cdev,
				   enum led_brightness brightness)
{
	struct iwl_mvm *mvm = container_of(led_cdev, struct iwl_mvm, led);
	if (brightness > 0)
		iwl_mvm_led_enable(mvm);
	else
		iwl_mvm_led_disable(mvm);
}
