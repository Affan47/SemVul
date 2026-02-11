screen_mssg_off (void)
{
	if (gos_curwin == gos_lower)
	{
		glk_put_char('\n');
		zargs[0] = 0;
		z_set_text_style();
		zargs[0] = oldstyle;
		z_set_text_style();
	}
}
