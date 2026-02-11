costly_cancel(struct obj *obj)
{
    char objroom;
    struct monst *shkp = (struct monst *)0;

    if (obj->no_charge) return;

    switch (obj->where)
    {
    case OBJ_INVENT:
        if (obj->unpaid)
        {
            shkp = shop_keeper(*u.ushops);
            if (!shkp) return;
            Norep("You cancel an unpaid object, you pay for it!");
            bill_dummy_object(obj);
        }
        break;
    case OBJ_FLOOR:
        objroom = *in_rooms(obj->ox, obj->oy, SHOPBASE);
        shkp = shop_keeper(objroom);
        if (!shkp || !inhishop(shkp)) return;
        if (costly_spot(u.ux, u.uy) && objroom == *u.ushops)
        {
            Norep("You cancel it, you pay for it!");
            bill_dummy_object(obj);
        }
        else
                stolen_value(obj, obj->ox, obj->oy, false, false);
        break;
    }
}
