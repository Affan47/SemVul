compare_cats(struct line_cats *ACats, struct line_cats *BCats)
{
    int i, j;

    if (ACats->n_cats == 0 || BCats->n_cats == 0) {
	if (ACats->n_cats == 0 && BCats->n_cats == 0)
	    return 0;

	if (ACats->n_cats == 0 && BCats->n_cats > 0)
	    return 1;

	if (ACats->n_cats > 0 && BCats->n_cats == 0)
	    return 1;
    }

    for (i = 0; i < ACats->n_cats; i++) {
	int found = 0;

	for (j = 0; j < BCats->n_cats; j++) {
	    if (ACats->cat[i] == BCats->cat[j] &&
	        ACats->field[i] == BCats->field[j]) {
		found = 1;
		break;
	    }
	}
	if (!found)
	    return 1;
    }

    return 0;
}
