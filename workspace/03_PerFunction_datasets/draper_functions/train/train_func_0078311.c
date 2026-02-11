imon_set_display_type(struct imon_context *ictx)
{
	u8 configured_display_type = IMON_DISPLAY_TYPE_VFD;


	if (display_type == IMON_DISPLAY_TYPE_AUTO) {
		switch (ictx->product) {
		case 0xffdc:

			configured_display_type = ictx->display_type;
			break;
		case 0x0034:
		case 0x0035:
			configured_display_type = IMON_DISPLAY_TYPE_VGA;
			break;
		case 0x0038:
		case 0x0039:
		case 0x0045:
			configured_display_type = IMON_DISPLAY_TYPE_LCD;
			break;
		case 0x003c:
		case 0x0041:
		case 0x0042:
		case 0x0043:
			configured_display_type = IMON_DISPLAY_TYPE_NONE;
			ictx->display_supported = false;
			break;
		case 0x0036:
		case 0x0044:
		default:
			configured_display_type = IMON_DISPLAY_TYPE_VFD;
			break;
		}
	} else {
		configured_display_type = display_type;
		if (display_type == IMON_DISPLAY_TYPE_NONE)
			ictx->display_supported = false;
		else
			ictx->display_supported = true;
		dev_info(ictx->dev, "%s: overriding display type to %d via "
			 "modparam\n", __func__, display_type);
	}

	ictx->display_type = configured_display_type;
}
