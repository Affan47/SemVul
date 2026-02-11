auok1901_update_region(struct auok190xfb_par *par, int mode,
						u16 y1, u16 y2)
{
	struct device *dev = par->info->device;
	unsigned char *buf = (unsigned char *)par->info->screen_base;
	int xres = par->info->var.xres;
	int line_length = par->info->fix.line_length;
	u16 args[5];

	pm_runtime_get_sync(dev);

	mutex_lock(&(par->io_lock));


	y1 &= 0xfffe;
	y2 &= 0xfffe;

	dev_dbg(dev, "update (x,y,w,h,mode)=(%d,%d,%d,%d,%d)\n",
		1, y1+1, xres, y2-y1, mode);


	args[0] = AUOK1901_DMA_ROTATE90(par->rotation) | 1;
	args[1] = y1 + 1;
	args[2] = xres;
	args[3] = y2 - y1;
	buf += y1 * line_length;
	auok190x_send_cmdargs_pixels_nowait(par, AUOK1901_CMD_DMA_START, 4,
					    args, ((y2 - y1) * line_length)/2,
					    (u16 *) buf);
	auok190x_send_command_nowait(par, AUOK190X_CMD_DATA_STOP);


	args[0] = mode | AUOK1901_DDMA_ROTATE180(par->rotation);
	args[1] = 1;
	args[2] = y1 + 1;
	args[3] = xres;
	args[4] = y2 - y1;
	auok190x_send_cmdargs_nowait(par, AUOK1901_CMD_DDMA_START, 5, args);

	par->update_cnt++;

	mutex_unlock(&(par->io_lock));

	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);
}
