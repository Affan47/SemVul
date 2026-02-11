clear_outside(const VSNodeBitmap *node, uint16 tile_x, uint16 tile_y, uint8 type, VNBTile *tile)
{
	int	x, y, bx, by, p;

	by = tile_y * VN_B_TILE_SIZE;
	for(y = p = 0; y < VN_B_TILE_SIZE; y++, by++)
	{
		bx = tile_x * VN_B_TILE_SIZE;
		for(x = 0; x < VN_B_TILE_SIZE; x++, bx++, p++)
		{

			if(bx >= node->size[0] || by >= node->size[1])
			{
				switch(type)
				{
				case VN_B_LAYER_UINT1:
					tile->vuint1[y] &= ~(128 >> x);
					break;
				case VN_B_LAYER_UINT8:
					tile->vuint8[p] = 0;
					break;
				case VN_B_LAYER_UINT16:
					tile->vuint16[p] = 0;
					break;
				case VN_B_LAYER_REAL32:
					tile->vreal32[p] = 0.0f;
					break;
				case VN_B_LAYER_REAL64:
					tile->vreal64[p] = 0.0;
					break;
				}
			}
		}
	}
}
