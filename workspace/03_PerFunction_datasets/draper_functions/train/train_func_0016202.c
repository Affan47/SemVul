initFbDev()
{
	s8 *fbdev = getenv("FRAMEBUFFER");

	if (fbdev) {
		fbdev_fd = open(fbdev, O_RDWR);
	} else {
		fbdev_fd = open("/dev/fb0", O_RDWR);
		if (fbdev_fd < 0) fbdev_fd = open("/dev/fb/0", O_RDWR);
	}

	if (fbdev_fd < 0) {
		fprintf(stderr, "can't open frame buffer device!\n");
		return 0;
	}

	fcntl(fbdev_fd, F_SETFD, fcntl(fbdev_fd, F_GETFD) | FD_CLOEXEC);
	ioctl(fbdev_fd, FBIOGET_FSCREENINFO, &finfo);
	ioctl(fbdev_fd, FBIOGET_VSCREENINFO, &vinfo);

	if (finfo.type != FB_TYPE_PACKED_PIXELS) {
		fprintf(stderr, "unsupported frame buffer device!\n");
		return 0;
	}

	switch (vinfo.bits_per_pixel) {
	case 8:
		if (finfo.visual != FB_VISUAL_PSEUDOCOLOR) {
			fprintf(stderr, "only support pseudo-color visual with 8bpp depth!\n");
			return 0;
		}
		break;

	case 15:
	case 16:
	case 32:
		if (finfo.visual != FB_VISUAL_TRUECOLOR && finfo.visual != FB_VISUAL_DIRECTCOLOR) {
			fprintf(stderr, "only support true-color/direct-color visual with 15/16/32bpp depth!\n");
			return 0;
		}
		break;

	default:
		fprintf(stderr, "only support frame buffer device with 8/15/16/32 color depth!\n");
		return 0;
	}

	return new FbDev();
}
