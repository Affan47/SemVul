cell_tile_style_new (GnmStyle *style, CellTileType t)
{
	CellTile *res = CHUNK_ALLOC (CellTile, t);
	*((CellTileType *)&(res->type)) = t;

	if (style != NULL) {
		int i = tile_size[t];
		gnm_style_link_multiple (style, i);
		while (--i >= 0)
			res->style_any.style[i] = style;
	}

	return res;
}
