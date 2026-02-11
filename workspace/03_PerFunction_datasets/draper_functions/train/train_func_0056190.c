icxcam_description(icxCAM which) {
	if (which == cam_default)
		which = icxcam_default();

	switch(which) {
		case cam_CIECAM97s3:
			return "CIECAM97s3";
		case cam_CIECAM02:
			return "CIECAM02";
		default:
			break;
	}
	return "Unknown CAM";
}
