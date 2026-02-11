init_buffered_spriteram(void)
{

	if (spriteram_size == 0)
	{
		logerror("vh_open():  Video buffers spriteram but spriteram_size is 0\n");
		return 0;
	}


	buffered_spriteram = auto_malloc(spriteram_size);
	if (!buffered_spriteram)
		return 1;


	state_save_register_UINT8("generic_video", 0, "buffered_spriteram", buffered_spriteram, spriteram_size);


	if (spriteram_2_size)
	{

		buffered_spriteram_2 = auto_malloc(spriteram_2_size);
		if (!buffered_spriteram_2)
			return 1;


		state_save_register_UINT8("generic_video", 0, "buffered_spriteram_2", buffered_spriteram_2, spriteram_2_size);
	}


	buffered_spriteram16 = (data16_t *)buffered_spriteram;
	buffered_spriteram32 = (data32_t *)buffered_spriteram;
	buffered_spriteram16_2 = (data16_t *)buffered_spriteram_2;
	buffered_spriteram32_2 = (data32_t *)buffered_spriteram_2;
	return 0;
}
