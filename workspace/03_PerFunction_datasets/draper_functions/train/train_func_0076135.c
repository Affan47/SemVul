vmap_count_adjacent(view_map_t *vmap, loc_t loc, char *adj_char)
{
    int i, count;
    loc_t new_loc;
    char *p;
    int len;

    len = strlen (adj_char);

    count = 0;

    FOR_ADJ_ON (loc, new_loc, i) {
	p = strchr (adj_char, vmap[new_loc].contents);
	if (p) count += 8 * (len - (p - adj_char));
    }
    return (count);
}
