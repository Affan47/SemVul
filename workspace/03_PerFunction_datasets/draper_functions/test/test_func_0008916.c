palmas_gpio_id_detect(struct work_struct *work)
{
	int id;
	struct palmas_usb *palmas_usb = container_of(to_delayed_work(work),
						     struct palmas_usb,
						     wq_detectid);
	struct extcon_dev *edev = palmas_usb->edev;

	if (!palmas_usb->id_gpiod)
		return;

	id = gpiod_get_value_cansleep(palmas_usb->id_gpiod);

	if (id) {
		extcon_set_cable_state_(edev, EXTCON_USB_HOST, false);
		dev_info(palmas_usb->dev, "USB-HOST cable is detached\n");
	} else {
		extcon_set_cable_state_(edev, EXTCON_USB_HOST, true);
		dev_info(palmas_usb->dev, "USB-HOST cable is attached\n");
	}
}
