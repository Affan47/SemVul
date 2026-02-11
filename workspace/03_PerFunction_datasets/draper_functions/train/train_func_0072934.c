fill_rooms(int *vis)
{
	int i;


	for (i = 0; i < total_rooms; i++) {
		if (!vis[i] && rooms[i].num_neighbors == 1) {
			fill_armory(i);
			vis[i] = 1;
		}
	}


	for (i = 0; i < total_rooms; i++) {
		if (!vis[i])
			mapgen_gift(&rooms[i]);
	}
}
