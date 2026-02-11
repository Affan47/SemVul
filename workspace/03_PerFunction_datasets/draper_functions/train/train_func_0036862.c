fill_out_urb(struct snd_usb_caiaqdev *cdev,
				struct urb *urb,
				const struct usb_iso_packet_descriptor *iso)
{
	switch (cdev->spec.data_alignment) {
	case 0:
	case 2:
		fill_out_urb_mode_0(cdev, urb, iso);
		break;
	case 3:
		fill_out_urb_mode_3(cdev, urb, iso);
		break;
	}
}
