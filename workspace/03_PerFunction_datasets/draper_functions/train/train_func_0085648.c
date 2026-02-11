ssd1307fb_remove(struct i2c_client *client)
{
	struct fb_info *info = i2c_get_clientdata(client);
	struct ssd1307fb_par *par = info->par;

	ssd1307fb_write_cmd(par->client, SSD1307FB_DISPLAY_OFF);

	backlight_device_unregister(info->bl_dev);

	unregister_framebuffer(info);
	if (par->device_info->need_pwm) {
		pwm_disable(par->pwm);
		pwm_put(par->pwm);
	};
	fb_deferred_io_cleanup(info);
	__free_pages(__va(info->fix.smem_start), get_order(info->fix.smem_len));
	framebuffer_release(info);

	return 0;
}
