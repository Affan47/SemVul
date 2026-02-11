disable_slot(struct hotplug_slot *hotplug_slot)
{
	struct slot *slot = hotplug_slot->private;
	int retval = 0;

	dbg("%s - physical_slot = %s", __func__, slot_name(slot));

	down_write(&list_rwsem);


	dbg("%s - unconfiguring slot %s", __func__, slot_name(slot));
	retval = cpci_unconfigure_slot(slot);
	if (retval) {
		err("%s - could not unconfigure slot %s",
		    __func__, slot_name(slot));
		goto disable_error;
	}
	dbg("%s - finished unconfiguring slot %s", __func__, slot_name(slot));


	if (cpci_clear_ext(slot)) {
		err("%s - could not clear EXT for slot %s",
		    __func__, slot_name(slot));
		retval = -ENODEV;
		goto disable_error;
	}
	cpci_led_on(slot);

	if (controller->ops->set_power) {
		retval = controller->ops->set_power(slot, 0);
		if (retval)
			goto disable_error;
	}

	if (update_adapter_status(slot->hotplug_slot, 0))
		warn("failure to update adapter file");

	if (slot->extracting) {
		slot->extracting = 0;
		atomic_dec(&extracting);
	}
disable_error:
	up_write(&list_rwsem);
	return retval;
}
