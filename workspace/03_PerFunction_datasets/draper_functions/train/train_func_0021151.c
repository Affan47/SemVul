merge_choice(struct obj *objlist, struct obj *obj)
{
    struct monst *shkp;
    int save_nocharge;

    if (obj->otyp == SCR_SCARE_MONSTER)
            return (struct obj *)0;


    save_nocharge = obj->no_charge;
    if (objlist == invent && obj->where == OBJ_FLOOR &&
        (shkp = shop_keeper(inside_shop(obj->ox, obj->oy))) != 0) {
        if (obj->no_charge) obj->no_charge = 0;


        else if (inhishop(shkp)) return (struct obj *)0;
    }
    while (objlist) {
        if (mergable(objlist, obj)) break;
        objlist = objlist->nobj;
    }
    obj->no_charge = save_nocharge;
    return objlist;
}
