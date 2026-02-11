generate_solution(ALI_MAP * map)
{
    ALI_MAP        *seg_map;
    unsigned long   map_pos, map_len;
    unsigned long   start_seg, end_seg, pos_seg;

    sub_solution = new ALI_SUB_SOLUTION(profile);

    map_len = map->last_base() - map->first_base() + 1;
    for (map_pos = map->first_base(); map_pos <= map->last_base(); map_pos++) {


        for (start_seg  = map_pos;
             start_seg <= map->last_base() && map->is_undefined(start_seg);
             start_seg++) ;

        if (start_seg <= map->last_base()) {
            for (end_seg  = start_seg;
                 end_seg <= map->last_base() && (!map->is_undefined(end_seg));
                 end_seg++) ;

            end_seg--;

            seg_map = new ALI_MAP(start_seg,
                                  end_seg,
                                  map->position(start_seg),
                                  map->position(end_seg));


            for (pos_seg = start_seg; pos_seg <= end_seg; pos_seg++) {
                if (map->is_inserted(pos_seg))
                    seg_map->set(pos_seg,
                                 map->position(pos_seg) - map->position(start_seg), 1);
                else
                    seg_map->set(pos_seg,
                                 map->position(pos_seg) - map->position(start_seg), 0);
            }

            if (sub_solution->insert(seg_map) != 1)
                ali_fatal_error("Inconsistent solution?",
                                "ALI_PREALIGNER::generate_solution()");

            map_pos = end_seg;
        }
    }
}
