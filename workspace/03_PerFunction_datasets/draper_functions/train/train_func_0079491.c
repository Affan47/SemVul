PC080SN_tilemap_update(void)
{
	int chip,j;

	for (chip = 0;chip < PC080SN_chips;chip++)
	{
		tilemap_set_scrolly(PC080SN_tilemap[chip][0],0,PC080SN_bgscrolly[chip][0]);
		tilemap_set_scrolly(PC080SN_tilemap[chip][1],0,PC080SN_bgscrolly[chip][1]);

		if (!PC080SN_dblwidth)
		{
			for (j = 0;j < 256;j++)
				tilemap_set_scrollx(PC080SN_tilemap[chip][0],
						(j + PC080SN_bgscrolly[chip][0]) & 0x1ff,
						PC080SN_bgscrollx[chip][0] - PC080SN_bgscroll_ram[chip][0][j]);
			for (j = 0;j < 256;j++)
				tilemap_set_scrollx(PC080SN_tilemap[chip][1],
						(j + PC080SN_bgscrolly[chip][1]) & 0x1ff,
						PC080SN_bgscrollx[chip][1] - PC080SN_bgscroll_ram[chip][1][j]);
		}
		else
		{
			tilemap_set_scrollx(PC080SN_tilemap[chip][0],0,PC080SN_bgscrollx[chip][0]);
			tilemap_set_scrollx(PC080SN_tilemap[chip][1],0,PC080SN_bgscrollx[chip][1]);
		}
	}
}
