kill_one(piece_info_t **list, piece_info_t *obj)
{
    UNLINK (list[obj->type], obj, piece_link);
    UNLINK (map[obj->loc].objp, obj, loc_link);
    disembark (obj);

    LINK (free_list, obj, piece_link);
    obj->hits = 0;
    obj->moved = piece_attr[obj->type].speed;
}
