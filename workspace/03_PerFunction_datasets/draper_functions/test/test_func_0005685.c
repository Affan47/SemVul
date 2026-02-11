v4l_requery(void) {
	if (raw_fb_fd < 0) {
		return;
	}
	v4l1_cap = v4l1_query(raw_fb_fd, 1);
	v4l2_cap = v4l2_query(raw_fb_fd, 1);
}
