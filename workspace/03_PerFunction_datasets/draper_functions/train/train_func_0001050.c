K054157_reset_tilemaps(void)
{
	int i;

	for(i=0; i<4; i++)
		K054157_tilemap[i] = K054157_tilemaps[i];
	for(i=0; i<4; i++)
		K054157_change_tilemap(i);
}
