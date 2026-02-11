read_in_urb(struct snd_usb_caiaqdev *cdev,
			const struct urb *urb,
			const struct usb_iso_packet_descriptor *iso)
{
	struct device *dev = caiaqdev_to_dev(cdev);

	if (!cdev->streaming)
		return;

	if (iso->actual_length < cdev->bpp)
		return;

	switch (cdev->spec.data_alignment) {
	case 0:
		read_in_urb_mode0(cdev, urb, iso);
		break;
	case 2:
		read_in_urb_mode2(cdev, urb, iso);
		break;
	case 3:
		read_in_urb_mode3(cdev, urb, iso);
		break;
	}

	if ((cdev->input_panic || cdev->output_panic) && !cdev->warned) {
		dev_warn(dev, "streaming error detected %s %s\n",
				cdev->input_panic ? "(input)" : "",
				cdev->output_panic ? "(output)" : "");
		cdev->warned = 1;
	}
}
