map_cont_edge(int *cont_map, loc_t loc)
{
    loc_t i, j;

    if (!cont_map[loc]) return false;

    FOR_ADJ (loc, j, i)
	if (!cont_map[j]) return true;

    return false;
}
