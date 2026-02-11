cell_tile_dtor (CellTile *tile)
{
	CellTileType t;

	g_return_if_fail (tile != NULL);

	t = tile->type;
	if (t == TILE_PTR_MATRIX) {
		int i = TILE_SIZE_COL * TILE_SIZE_ROW;
		while (--i >= 0) {
			cell_tile_dtor (tile->ptr_matrix.ptr[i]);
			tile->ptr_matrix.ptr[i] = NULL;
		}
	} else if (TILE_SIMPLE <= t && t <= TILE_MATRIX) {
		int i = tile_size[t];
		while (--i >= 0) {
			gnm_style_unlink (tile->style_any.style[i]);
			tile->style_any.style[i] = NULL;
		}
	} else {
		g_return_if_fail (FALSE);
	}

	*((CellTileType *)&(tile->type)) = TILE_UNDEFINED;
	CHUNK_FREE (t, tile);
}
