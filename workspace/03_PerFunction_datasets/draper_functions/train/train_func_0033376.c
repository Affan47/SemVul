valid_pix(struct vivid_dev *dev, int win_y, int win_x, int fb_y, int fb_x)
{
	int i;

	if (dev->bitmap_cap) {


		const u8 *p = dev->bitmap_cap;
		unsigned stride = (dev->compose_cap.width + 7) / 8;

		if (!(p[stride * win_y + win_x / 8] & (1 << (win_x & 7))))
			return false;
	}

	for (i = 0; i < dev->clipcount_cap; i++) {


		struct v4l2_rect *r = &dev->clips_cap[i].c;

		if (fb_y >= r->top && fb_y < r->top + r->height &&
		    fb_x >= r->left && fb_x < r->left + r->width)
			return false;
	}
	return true;
}
