delobj(struct obj *obj)
{
    bool update_map;

    if (obj->otyp == AMULET_OF_YENDOR ||
        obj->otyp == CANDELABRUM_OF_INVOCATION ||
        obj->otyp == BELL_OF_OPENING ||
        obj->otyp == SPE_BOOK_OF_THE_DEAD) {


        return;
    }
    update_map = (obj->where == OBJ_FLOOR);
    obj_extract_self(obj);
    if (update_map) newsym(obj->ox, obj->oy);
    obfree(obj, NULL);
}
