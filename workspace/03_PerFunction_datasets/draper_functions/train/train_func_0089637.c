gsc_try_fmt_mplane(struct gsc_ctx *ctx, struct v4l2_format *f)
{
	struct gsc_dev *gsc = ctx->gsc_dev;
	struct gsc_variant *variant = gsc->variant;
	struct v4l2_pix_format_mplane *pix_mp = &f->fmt.pix_mp;
	const struct gsc_fmt *fmt;
	u32 max_w, max_h, mod_x, mod_y;
	u32 min_w, min_h, tmp_w, tmp_h;
	int i;

	pr_debug("user put w: %d, h: %d", pix_mp->width, pix_mp->height);

	fmt = find_fmt(&pix_mp->pixelformat, NULL, 0);
	if (!fmt) {
		pr_err("pixelformat format (0x%X) invalid\n",
						pix_mp->pixelformat);
		return -EINVAL;
	}

	if (pix_mp->field == V4L2_FIELD_ANY)
		pix_mp->field = V4L2_FIELD_NONE;
	else if (pix_mp->field != V4L2_FIELD_NONE) {
		pr_err("Not supported field order(%d)\n", pix_mp->field);
		return -EINVAL;
	}

	max_w = variant->pix_max->target_rot_dis_w;
	max_h = variant->pix_max->target_rot_dis_h;

	mod_x = ffs(variant->pix_align->org_w) - 1;
	if (is_yuv420(fmt->color))
		mod_y = ffs(variant->pix_align->org_h) - 1;
	else
		mod_y = ffs(variant->pix_align->org_h) - 2;

	if (V4L2_TYPE_IS_OUTPUT(f->type)) {
		min_w = variant->pix_min->org_w;
		min_h = variant->pix_min->org_h;
	} else {
		min_w = variant->pix_min->target_rot_dis_w;
		min_h = variant->pix_min->target_rot_dis_h;
	}

	pr_debug("mod_x: %d, mod_y: %d, max_w: %d, max_h = %d",
			mod_x, mod_y, max_w, max_h);


	tmp_w = pix_mp->width;
	tmp_h = pix_mp->height;

	v4l_bound_align_image(&pix_mp->width, min_w, max_w, mod_x,
		&pix_mp->height, min_h, max_h, mod_y, 0);
	if (tmp_w != pix_mp->width || tmp_h != pix_mp->height)
		pr_info("Image size has been modified from %dx%d to %dx%d",
			 tmp_w, tmp_h, pix_mp->width, pix_mp->height);

	pix_mp->num_planes = fmt->num_planes;

	if (pix_mp->width >= 1280)
		pix_mp->colorspace = V4L2_COLORSPACE_REC709;
	else
		pix_mp->colorspace = V4L2_COLORSPACE_SMPTE170M;


	for (i = 0; i < pix_mp->num_planes; ++i) {
		int bpl = (pix_mp->width * fmt->depth[i]) >> 3;
		pix_mp->plane_fmt[i].bytesperline = bpl;
		pix_mp->plane_fmt[i].sizeimage = bpl * pix_mp->height;

		pr_debug("[%d]: bpl: %d, sizeimage: %d",
				i, bpl, pix_mp->plane_fmt[i].sizeimage);
	}

	return 0;
}
