Vect_cidx_find_all(struct Map_info *Map, int layer, int type_mask,
			int cat, struct ilist *lines)
{
    int type, line;
    struct Cat_index *ci;
    int field_index, idx;

    Vect_reset_list(lines);
    field_index = Vect_cidx_get_field_index(Map, layer);

    if (field_index == -1) {

	return;
    }
    ci = &(Map->plus.cidx[field_index]);

    idx = Vect_cidx_find_next(Map, field_index, cat,
			      type_mask, 0, &type, &line);

    if (idx == -1) {
	return;
    }

    do {
	if (ci->cat[idx][0] != cat) {
	    break;
	}
	if (ci->cat[idx][1] & type_mask) {
	    Vect_list_append(lines, ci->cat[idx][2]);
	}
	idx++;
    } while (idx < ci->n_cats);
    return;
}
