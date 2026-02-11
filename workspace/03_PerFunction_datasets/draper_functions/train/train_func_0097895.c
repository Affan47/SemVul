key_flush()
{
 	int i;
	Uint8 *keystate = SDL_GetKeyState(NULL);

	if (!Installed)
		key_init();


	for (i=0; i<KEY_BUFFER_SIZE; i++ )
		unicode_frame_buffer[i] = '\0';

	for (i=0; i<256; i++ )	{
		if (key_ismodlck(i) == KEY_ISLCK && keystate[key_properties[i].sym] && !GameArg.CtlNoStickyKeys)
		{
			keyd_pressed[i] = 1;
			key_data.state[i] = 0;
		}
		else
		{
			keyd_pressed[i] = 0;
			key_data.state[i] = 1;
		}
	}
}
