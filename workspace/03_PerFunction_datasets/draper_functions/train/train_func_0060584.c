rmaps_lama_find_parent(hwloc_topology_t hwloc_topo,
                                     hwloc_obj_t *child_obj,
                                     rmaps_lama_level_type_t lama_key)
{
    hwloc_obj_t *cur_parent = NULL;
    hwloc_obj_type_t hwloc_key;
    int depth;

    cur_parent = (hwloc_obj_t*)malloc(sizeof(hwloc_obj_t) * 1);


    rmaps_lama_convert_lama_key_to_hwloc_key(lama_key, &hwloc_key, &depth);


    if( hwloc_key == (*child_obj)->type ) {
        if( HWLOC_OBJ_CACHE == (*child_obj)->type &&
            depth == (int)(*child_obj)->attr->cache.depth ) {
            return child_obj;
        } else {
            return child_obj;
        }
    }


    *cur_parent = (*child_obj)->parent;
    while(NULL != *cur_parent ) {
        if( hwloc_key == (*cur_parent)->type ) {
            if( HWLOC_OBJ_CACHE == (*cur_parent)->type &&
                depth == (int)(*cur_parent)->attr->cache.depth ) {
                return cur_parent;
            } else {
                return cur_parent;
            }
        }

        *cur_parent = (*cur_parent)->parent;
    }

    free(cur_parent);
    return NULL;
}
