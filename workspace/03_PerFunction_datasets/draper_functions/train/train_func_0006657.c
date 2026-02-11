get_new_tile (void)
{
	int i;
	int min, max, min_index, max_index, previous_min_index;

	min_index = 0;
	previous_min_index = 0;
	max_index = 0;
	min = gi_nb_of_tiles[0];
	max = gi_nb_of_tiles[0];
	for (i = 0; i < 7; i++) {
		if (gi_nb_of_tiles[i] < min) {
			min = gi_nb_of_tiles[i];
			min_index = i;
			previous_min_index = min_index;
		}
		if (gi_nb_of_tiles[i] > max) {
			max = gi_nb_of_tiles[i];
			max_index = i;
		}
	}

	i = (gint) g_rand_int_range (g_random_generator, 0, 2);

	switch (i) {
	case 0:
		return g_rand_int_range (g_random_generator, 0, 2) ? min_index : previous_min_index;
	default:
		return (max_index + (gchar) g_rand_int_range (g_random_generator, 1, 7)) % 7;
	}
}
