cps1_find_last_sprite(void)
{
    int offset=0;

    while (offset < cps1_obj_size/2)
	{
        int colour=cps1_buffered_obj[offset+3];
		if (colour == 0xff00)
		{

            cps1_last_sprite_offset=offset-4;
			return;
		}
        offset+=4;
	}

    cps1_last_sprite_offset=cps1_obj_size/2-4;
}
