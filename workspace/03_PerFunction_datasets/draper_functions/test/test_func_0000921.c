select_part_type(pixel_set *set)
{

    if ((set->width == 1) && (set->height == 1)) {
        set->type = TYPE_POINT;
    } else if ((set->width == 0) || (set->height == 0)) {
        set->type = TYPE_EMPTY;
    } else {
        set->type = TYPE_S;
    }
}
