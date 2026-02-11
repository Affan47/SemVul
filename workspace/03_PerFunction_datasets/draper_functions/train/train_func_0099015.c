set_graph_palette_from_string (int i, const char *s)
{
    int err = 0;

    if (i >= 0 && i < N_GP_COLORS) {
	unsigned int x[3];

	if (sscanf(s + 1, "%02x%02x%02x", &x[0], &x[1], &x[2]) == 3) {
	    user_color[i].r = x[0];
	    user_color[i].g = x[1];
	    user_color[i].b = x[2];
	} else {
	    err = 1;
	}
    } else {
	err = 1;
    }

    if (err) {
	fprintf(stderr, "Error in set_graph_palette_from_string(%d, '%s')\n",
		i, s);
    }
}
