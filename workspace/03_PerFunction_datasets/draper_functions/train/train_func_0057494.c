fracture_rock(struct obj *obj)
{

    if (obj->otyp == BOULDER && In_sokoban(&u.uz) && !flags.mon_moving)
            change_luck(-1);

    obj->otyp = ROCK;
    obj->quan = (long) rn1(60, 7);
    obj->owt = weight(obj);
    obj->oclass = GEM_CLASS;
    obj->known = false;
    obj->onamelth = 0;
    obj->oxlth = 0;
    obj->oattached = OATTACHED_NOTHING;
    if (obj->where == OBJ_FLOOR)
    {
        obj_extract_self(obj);
        place_object(obj, obj->ox, obj->oy);
        if(!does_block(obj->ox,obj->oy,&levl[obj->ox][obj->oy]))
                unblock_point(obj->ox,obj->oy);
        if(cansee(obj->ox,obj->oy))
                newsym(obj->ox,obj->oy);
    }
}
