fimc_cap_s_selection(struct file *file, void *fh,
				struct v4l2_selection *s)
{
	struct fimc_dev *fimc = video_drvdata(file);
	struct fimc_ctx *ctx = fimc->vid_cap.ctx;
	struct v4l2_rect rect = s->r;
	struct fimc_frame *f;
	unsigned long flags;

	if (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		return -EINVAL;

	if (s->target == V4L2_SEL_TGT_COMPOSE)
		f = &ctx->d_frame;
	else if (s->target == V4L2_SEL_TGT_CROP)
		f = &ctx->s_frame;
	else
		return -EINVAL;

	fimc_capture_try_selection(ctx, &rect, s->target);

	if (s->flags & V4L2_SEL_FLAG_LE &&
	    !enclosed_rectangle(&rect, &s->r))
		return -ERANGE;

	if (s->flags & V4L2_SEL_FLAG_GE &&
	    !enclosed_rectangle(&s->r, &rect))
		return -ERANGE;

	s->r = rect;
	spin_lock_irqsave(&fimc->slock, flags);
	set_frame_crop(f, s->r.left, s->r.top, s->r.width,
		       s->r.height);
	spin_unlock_irqrestore(&fimc->slock, flags);

	set_bit(ST_CAPT_APPLY_CFG, &fimc->state);
	return 0;
}
