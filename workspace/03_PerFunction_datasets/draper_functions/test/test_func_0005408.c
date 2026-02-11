insert_multisquare_ob_in_map(object *new_obj, mapstruct *map) {
    int x, y;
    archetype *at;
    object *old_seg;
    object *head;


    object_insert_in_map(new_obj, map, new_obj, INS_NO_MERGE|INS_NO_WALK_ON);

    x = new_obj->x;
    y = new_obj->y;
    old_seg = new_obj;
    head = new_obj;
    for (at = new_obj->arch->more; at != NULL; at = at->more) {
        object *new_seg;

        new_seg = arch_to_object(at);
        new_seg->x = x+at->clone.x;
        new_seg->y = y+at->clone.y;
        new_seg->map = old_seg->map;
        object_insert_in_map(new_seg, new_seg->map, new_seg, INS_NO_MERGE|INS_NO_WALK_ON);
        new_seg->head = head;
        old_seg->more = new_seg;
        old_seg = new_seg;
    }
    old_seg->more = NULL;
}
