detatwin_sprite_callback(int *code,int *color,int *priority_mask)
{
#if 0
if (keyboard_pressed(KEYCODE_Q) && (*color & 0x20)) *color = rand();
if (keyboard_pressed(KEYCODE_W) && (*color & 0x40)) *color = rand();
if (keyboard_pressed(KEYCODE_E) && (*color & 0x80)) *color = rand();
#endif
	int pri = 0x20 | ((*color & 0x60) >> 2);
	if (pri <= layerpri[2])								*priority_mask = 0;
	else if (pri > layerpri[2] && pri <= layerpri[1])	*priority_mask = 0xf0;
	else if (pri > layerpri[1] && pri <= layerpri[0])	*priority_mask = 0xf0|0xcc;
	else 												*priority_mask = 0xf0|0xcc|0xaa;

	*color = sprite_colorbase + (*color & 0x1f);
}
