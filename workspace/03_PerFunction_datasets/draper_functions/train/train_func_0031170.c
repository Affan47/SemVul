vt102_monitor_vert_retrace(void *_cpssp)
{
	struct cpssp *cpssp = (struct cpssp *) _cpssp;

	cpssp->height = cpssp->y;

	if (cpssp->width != cpssp->last_width
	 || cpssp->height != cpssp->last_height) {

		if (cpssp->height < cpssp->last_height && cpssp->last_height != -1) {


			while (cpssp->y < cpssp->last_height) {
				while (cpssp->x < cpssp->last_width) {
					vt102_monitor_out(cpssp, 0, 0, 0);
				}
				cpssp->x = 0;
				cpssp->y++;
				cpssp->write_pointer = &cpssp->pixel_buffer[cpssp->y * MAX_WIDTH * 4];
			}
		}

		cpssp->last_width = cpssp->width;
		cpssp->last_height = cpssp->height;

		sig_opt_rgb_size_set(cpssp->port_opt_video, cpssp, cpssp->width, cpssp->height);
	}

	cpssp->y = 0;

	cpssp->write_pointer = &cpssp->pixel_buffer[0];

	sig_opt_rgb_sync(cpssp->port_opt_video, cpssp);
}
