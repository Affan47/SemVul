fb_clear_screen(void)
{
    if (visible)
	fb_memset(fb_mem,0,fb_fix.line_length * fb_var.yres);
}
