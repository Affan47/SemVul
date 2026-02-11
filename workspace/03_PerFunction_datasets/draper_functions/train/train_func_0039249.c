bttv_get_width_mask_vid_cap(const struct bttv_format *fmt,
					unsigned int *width_mask,
					unsigned int *width_bias)
{
	if (fmt->flags & FORMAT_FLAGS_PLANAR) {
		*width_mask = ~15;
		*width_bias = 8;
	} else {
		*width_mask = ~3;
		*width_bias = 2;
	}
}
