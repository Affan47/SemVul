dig_area_add_isle(struct Plus_head *plus, int area, int isle)
{
    int i;
    P_AREA *Area;

    G_debug(3, "dig_area_add_isle(): area = %d isle = %d", area, isle);

    Area = plus->Area[area];
    if (Area == NULL)
	G_fatal_error("Attempt to add isle to dead area");

    for (i = 0; i < Area->n_isles; i++) {
	if (Area->isles[i] == isle) {
	    G_debug(3, "isle already registered in area");
	    return 0;
	}
    }

    if (Area->alloc_isles <= Area->n_isles)
	dig_area_alloc_isle(Area, 1);

    Area->isles[Area->n_isles] = isle;
    Area->n_isles++;
    G_debug(3, "  -> n_isles = %d", Area->n_isles);

    return 0;
}
