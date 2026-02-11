TC0100SCN_ctrl_word_w(int chip,offs_t offset,data16_t data,UINT32 mem_mask)
{
	COMBINE_DATA(&TC0100SCN_ctrl[chip][offset]);

	data = TC0100SCN_ctrl[chip][offset];

	switch (offset)
	{
		case 0x00:
			TC0100SCN_bgscrollx[chip] = -data;
			break;

		case 0x01:
			TC0100SCN_fgscrollx[chip] = -data;
			break;

		case 0x02:
			tilemap_set_scrollx(TC0100SCN_tilemap[chip][2][0],0,-data);
			tilemap_set_scrollx(TC0100SCN_tilemap[chip][2][1],0,-data);
			break;

		case 0x03:
			TC0100SCN_bgscrolly[chip] = -data;
			break;

		case 0x04:
			TC0100SCN_fgscrolly[chip] = -data;
			break;

		case 0x05:
			tilemap_set_scrolly(TC0100SCN_tilemap[chip][2][0],0,-data);
			tilemap_set_scrolly(TC0100SCN_tilemap[chip][2][1],0,-data);
			break;

		case 0x06:
		{
			int old_width = TC0100SCN_dblwidth[chip];
			TC0100SCN_dblwidth[chip] = (data &0x10) >> 4;

			if (TC0100SCN_dblwidth[chip] != old_width)
			{

				TC0100SCN_set_layer_ptrs(chip);


				TC0100SCN_dirty_tilemaps(chip);
			}

			break;
		}

		case 0x07:
		{
			int flip = (data & 0x01) ? (TILEMAP_FLIPX | TILEMAP_FLIPY) : 0;

			tilemap_set_flip(TC0100SCN_tilemap[chip][0][0],flip);
			tilemap_set_flip(TC0100SCN_tilemap[chip][1][0],flip);
			tilemap_set_flip(TC0100SCN_tilemap[chip][2][0],flip);
			tilemap_set_flip(TC0100SCN_tilemap[chip][0][1],flip);
			tilemap_set_flip(TC0100SCN_tilemap[chip][1][1],flip);
			tilemap_set_flip(TC0100SCN_tilemap[chip][2][1],flip);

			break;
		}
	}
}
