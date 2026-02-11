vsxxxaa_connect(struct serio *serio, struct serio_driver *drv)
{
	struct vsxxxaa *mouse;
	struct input_dev *input_dev;
	int err = -ENOMEM;

	mouse = kzalloc(sizeof(struct vsxxxaa), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!mouse || !input_dev)
		goto fail1;

	mouse->dev = input_dev;
	mouse->serio = serio;
	strlcat(mouse->name, "DEC VSXXX-AA/-GA mouse or VSXXX-AB digitizer",
		 sizeof(mouse->name));
	snprintf(mouse->phys, sizeof(mouse->phys), "%s/input0", serio->phys);

	input_dev->name = mouse->name;
	input_dev->phys = mouse->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->dev.parent = &serio->dev;

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(EV_REL, input_dev->evbit);
	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(BTN_LEFT, input_dev->keybit);
	__set_bit(BTN_MIDDLE, input_dev->keybit);
	__set_bit(BTN_RIGHT, input_dev->keybit);
	__set_bit(BTN_TOUCH, input_dev->keybit);
	__set_bit(REL_X, input_dev->relbit);
	__set_bit(REL_Y, input_dev->relbit);
	input_set_abs_params(input_dev, ABS_X, 0, 1023, 0, 0);
	input_set_abs_params(input_dev, ABS_Y, 0, 1023, 0, 0);

	serio_set_drvdata(serio, mouse);

	err = serio_open(serio, drv);
	if (err)
		goto fail2;


	serio_write(serio, 'T');

	err = input_register_device(input_dev);
	if (err)
		goto fail3;

	return 0;

 fail3:	serio_close(serio);
 fail2:	serio_set_drvdata(serio, NULL);
 fail1:	input_free_device(input_dev);
	kfree(mouse);
	return err;
}
