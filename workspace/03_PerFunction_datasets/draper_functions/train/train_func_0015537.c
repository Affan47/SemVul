shuffle_tiles()
{
	int i;
	short tmp_tilemap[NUM_OBJECTS];

	for (i = 0; i < NUM_OBJECTS; i++)
		tmp_tilemap[i] =
			glyph2tile[objects[i].oc_descr_idx + GLYPH_OBJ_OFF];

	for (i = 0; i < NUM_OBJECTS; i++)
		glyph2tile[i + GLYPH_OBJ_OFF] = tmp_tilemap[i];
}
