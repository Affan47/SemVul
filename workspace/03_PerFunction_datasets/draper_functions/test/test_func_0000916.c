mia_tile_callback(int layer,int bank,int *code,int *color)
{
	tile_info.flags = (*color & 0x04) ? TILE_FLIPX : 0;
	if (layer == 0)
	{
		*code |= ((*color & 0x01) << 8);
		*color = layer_colorbase[layer] + ((*color & 0x80) >> 5) + ((*color & 0x10) >> 1);
	}
	else
	{
		*code |= ((*color & 0x01) << 8) | ((*color & 0x18) << 6) | (bank << 11);
		*color = layer_colorbase[layer] + ((*color & 0xe0) >> 5);
	}
}
