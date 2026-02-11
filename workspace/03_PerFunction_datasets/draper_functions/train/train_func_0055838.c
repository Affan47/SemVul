mapgen_draw_room(int room_id)
{
	int place_x = rooms[room_id].x - 1;
  	int	place_y = rooms[room_id].y - 1;
	int room_w = rooms[room_id].w + 1;
	int room_h = rooms[room_id].h + 1;
	int x, y, i;


	mapgen_put_tile(place_x, place_y, TILE_WALL, -1);
	mapgen_put_tile(place_x + room_w, place_y, TILE_WALL, -1);
	mapgen_put_tile(place_x, place_y + room_h, TILE_WALL, -1);
	mapgen_put_tile(place_x + room_w, place_y + room_h, TILE_WALL, -1);


	for (i = 1; i < room_w; i++) {
		mapgen_put_tile(place_x + i, place_y + room_h, TILE_WALL, -1);
		mapgen_put_tile(place_x + i, place_y, TILE_WALL, -1);
	}
	for (i = 1; i < room_h; i++) {
		mapgen_put_tile(place_x + room_w, place_y + i, TILE_WALL, -1);
		mapgen_put_tile(place_x, place_y + i, TILE_WALL, -1);
	}


	for (y = 1; y < room_h; y++)
		for (x = 1; x < room_w; x++)
			mapgen_put_tile(place_x + x, place_y + y, TILE_FLOOR, room_id);
}
