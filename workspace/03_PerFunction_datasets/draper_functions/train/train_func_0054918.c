render_sprite_row(UINT16 *sprite_source, UINT32 address)
{
	int flipxor = ((*btoads_sprite_control >> 10) & 1) ? 0xffff : 0x0000;
	int width = (~*btoads_sprite_control & 0x1ff) + 2;
	int color = (~*btoads_sprite_control >> 8) & 0xf0;
	int srcoffs = sprite_source_offs << 8;
	int srcend = srcoffs + (width << 8);
	int srcstep = 0x100 - btoads_sprite_scale[0];
	int dststep = 0x100 - btoads_sprite_scale[8];
	int dstoffs = sprite_dest_offs << 8;


	if (!(misc_control & 0x10))
	{
		for ( ; srcoffs < srcend; srcoffs += srcstep, dstoffs += dststep)
		{
			UINT16 src = sprite_source[(srcoffs >> 10) & 0x1ff];
			if (src)
			{
				src = (src >> (((srcoffs ^ flipxor) >> 6) & 0x0c)) & 0x0f;
				if (src)
					sprite_dest_base[(dstoffs >> 8) & 0x1ff] = src | color;
			}
		}
	}


	else
	{
		for ( ; srcoffs < srcend; srcoffs += srcstep, dstoffs += dststep)
		{
			UINT16 src = sprite_source[(srcoffs >> 10) & 0x1ff];
			if (src)
			{
				src = (src >> (((srcoffs ^ flipxor) >> 6) & 0x0c)) & 0x0f;
				if (src)
					sprite_dest_base[(dstoffs >> 8) & 0x1ff] = color;
			}
		}
	}

	sprite_source_offs += width;
	sprite_dest_offs = dstoffs >> 8;
}
