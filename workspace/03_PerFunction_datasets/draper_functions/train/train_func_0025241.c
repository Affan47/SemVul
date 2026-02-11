split_wall(int w, int h, unsigned char *tiles)
{
	int y, x;
	int room;
#define SET(X,Y,TILE) mapgen_put_tile(X, Y, TILE, room)


	for (x = 0; x < total_rooms; x++) {
		if (rooms[x].x + rooms[x].w < w - 1 )
			rooms[x].w--;
		if (rooms[x].y + rooms[x].h < h - 1)
			rooms[x].h--;
	}

	for (y = 1; y < h - 1; y++)
		for (x = 1; x < w - 1; x++) {
			room = mapgen_get_room(x, y);
			if (tiles[y * w + x] == TILE_WALL) {
				SET(x - 1, y    , TILE_WALL);
				SET(x    , y - 1, TILE_WALL);
				SET(x - 1, y - 1, TILE_WALL);
			}
		}
}
