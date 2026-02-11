ses_set_active(struct enclosure_device *edev,
			  struct enclosure_component *ecomp,
			  enum enclosure_component_setting val)
{
	unsigned char desc[4];
	unsigned char *desc_ptr;

	desc_ptr = ses_get_page2_descriptor(edev, ecomp);

	if (!desc_ptr)
		return -EIO;

	init_device_slot_control(desc, ecomp, desc_ptr);

	switch (val) {
	case ENCLOSURE_SETTING_DISABLED:
		desc[2] &= 0x7f;
		ecomp->active = 0;
		break;
	case ENCLOSURE_SETTING_ENABLED:
		desc[2] |= 0x80;
		ecomp->active = 1;
		break;
	default:

		return -EINVAL;
	}
	return ses_set_page2_descriptor(edev, ecomp, desc);
}
