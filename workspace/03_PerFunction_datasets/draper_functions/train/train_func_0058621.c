print_dv_timings(const struct v4l2_dv_timings *t)
{
	const struct v4l2_bt_timings *bt;
	double tot_width, tot_height;

	switch (t->type) {
	case V4L2_DV_BT_656_1120:
		bt = &t->bt;

		tot_height = bt->height +
			bt->vfrontporch + bt->vsync + bt->vbackporch +
			bt->il_vfrontporch + bt->il_vsync + bt->il_vbackporch;
		tot_width = bt->width +
			bt->hfrontporch + bt->hsync + bt->hbackporch;
		if (options[OptConcise]) {
			printf("\t%dx%d%c%.2f %s\n", bt->width, bt->height,
				bt->interlaced ? 'i' : 'p',
				(double)bt->pixelclock /
					(tot_width * (tot_height / (bt->interlaced ? 2 : 1))),
				flags2s(bt->flags, dv_flags_def).c_str());
			break;
		}
		printf("\tActive width: %d\n", bt->width);
		printf("\tActive height: %d\n", bt->height);
		printf("\tTotal width: %d\n",bt->width +
				bt->hfrontporch + bt->hsync + bt->hbackporch);
		printf("\tTotal height: %d\n", bt->height +
				bt->vfrontporch + bt->vsync + bt->vbackporch +
				bt->il_vfrontporch + bt->il_vsync + bt->il_vbackporch);

		printf("\tFrame format: %s\n", bt->interlaced ? "interlaced" : "progressive");
		printf("\tPolarities: %cvsync %chsync\n",
				(bt->polarities & V4L2_DV_VSYNC_POS_POL) ? '+' : '-',
				(bt->polarities & V4L2_DV_HSYNC_POS_POL) ? '+' : '-');
		printf("\tPixelclock: %lld Hz", bt->pixelclock);
		if (bt->width && bt->height) {
			if (bt->interlaced)
				printf(" (%.2f fields per second)", (double)bt->pixelclock /
					(tot_width * (tot_height / 2)));
			else
				printf(" (%.2f frames per second)", (double)bt->pixelclock /
					(tot_width * tot_height));
		}
		printf("\n");
		printf("\tHorizontal frontporch: %d\n", bt->hfrontporch);
		printf("\tHorizontal sync: %d\n", bt->hsync);
		printf("\tHorizontal backporch: %d\n", bt->hbackporch);
		if (bt->interlaced)
			printf("\tField 1:\n");
		printf("\tVertical frontporch: %d\n", bt->vfrontporch);
		printf("\tVertical sync: %d\n", bt->vsync);
		printf("\tVertical backporch: %d\n", bt->vbackporch);
		if (bt->interlaced) {
			printf("\tField 2:\n");
			printf("\tVertical frontporch: %d\n", bt->il_vfrontporch);
			printf("\tVertical sync: %d\n", bt->il_vsync);
			printf("\tVertical backporch: %d\n", bt->il_vbackporch);
		}
		printf("\tStandards: %s\n", flags2s(bt->standards, dv_standards_def).c_str());
		printf("\tFlags: %s\n", flags2s(bt->flags, dv_flags_def).c_str());
		break;
	default:
		printf("Timing type not defined\n");
		break;
	}
}
