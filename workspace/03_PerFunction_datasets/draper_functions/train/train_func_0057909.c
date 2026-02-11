add_id_mapping(gid, nid)
    unsigned gid, nid;
{
    int idx;

    idx = n_ids_mapped % N_PER_BUCKET;


    if (idx == 0) {
	struct bucket *gnu = (struct bucket *) alloc(sizeof(struct bucket));
	gnu->next = id_map;
	id_map = gnu;
    }

    id_map->map[idx].gid = gid;
    id_map->map[idx].nid = nid;
    n_ids_mapped++;
}
