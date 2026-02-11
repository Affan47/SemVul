place_should_be_logged(const char *place)
{
    int i;

    if (num_places == 0)
	return 1;
    for (i = 0; i < num_places; ++i) {
	if (*loggable_places[i] != '-' &&
	    place_matches(place, loggable_places[i]))
		return 1;
    }
    return 0;
}
