vivid_precalc_copy_rects(struct vivid_dev *dev)
{

	struct v4l2_rect r_fb = {
		0, 0, dev->display_width, dev->display_height
	};

	struct v4l2_rect r_overlay = {
		dev->overlay_out_left, dev->overlay_out_top,
		dev->compose_out.width, dev->compose_out.height
	};

	dev->loop_vid_copy = rect_intersect(&dev->crop_cap, &dev->compose_out);

	dev->loop_vid_out = dev->loop_vid_copy;
	rect_scale(&dev->loop_vid_out, &dev->compose_out, &dev->crop_out);
	dev->loop_vid_out.left += dev->crop_out.left;
	dev->loop_vid_out.top += dev->crop_out.top;

	dev->loop_vid_cap = dev->loop_vid_copy;
	rect_scale(&dev->loop_vid_cap, &dev->crop_cap, &dev->compose_cap);

	dprintk(dev, 1,
		"loop_vid_copy: %dx%d@%dx%d loop_vid_out: %dx%d@%dx%d loop_vid_cap: %dx%d@%dx%d\n",
		dev->loop_vid_copy.width, dev->loop_vid_copy.height,
		dev->loop_vid_copy.left, dev->loop_vid_copy.top,
		dev->loop_vid_out.width, dev->loop_vid_out.height,
		dev->loop_vid_out.left, dev->loop_vid_out.top,
		dev->loop_vid_cap.width, dev->loop_vid_cap.height,
		dev->loop_vid_cap.left, dev->loop_vid_cap.top);

	r_overlay = rect_intersect(&r_fb, &r_overlay);


	r_overlay.left += dev->compose_out.left - dev->overlay_out_left;
	r_overlay.top += dev->compose_out.top - dev->overlay_out_top;

	dev->loop_vid_overlay = rect_intersect(&r_overlay, &dev->loop_vid_copy);
	dev->loop_fb_copy = dev->loop_vid_overlay;


	dev->loop_fb_copy.left -= dev->compose_out.left - dev->overlay_out_left;
	dev->loop_fb_copy.top -= dev->compose_out.top - dev->overlay_out_top;

	dev->loop_vid_overlay_cap = dev->loop_vid_overlay;
	rect_scale(&dev->loop_vid_overlay_cap, &dev->crop_cap, &dev->compose_cap);

	dprintk(dev, 1,
		"loop_fb_copy: %dx%d@%dx%d loop_vid_overlay: %dx%d@%dx%d loop_vid_overlay_cap: %dx%d@%dx%d\n",
		dev->loop_fb_copy.width, dev->loop_fb_copy.height,
		dev->loop_fb_copy.left, dev->loop_fb_copy.top,
		dev->loop_vid_overlay.width, dev->loop_vid_overlay.height,
		dev->loop_vid_overlay.left, dev->loop_vid_overlay.top,
		dev->loop_vid_overlay_cap.width, dev->loop_vid_overlay_cap.height,
		dev->loop_vid_overlay_cap.left, dev->loop_vid_overlay_cap.top);
}
