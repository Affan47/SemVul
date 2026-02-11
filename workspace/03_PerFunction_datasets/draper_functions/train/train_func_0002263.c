killer_xname(struct obj *obj)
{
    struct obj save_obj;
    unsigned save_ocknown;
    char *buf, *save_ocuname;


    save_obj = *obj;


    obj->known = obj->dknown = 1;
    obj->bknown = obj->rknown = obj->greased = 0;

    obj->blessed = obj->cursed = 0;


    obj->opoisoned = 0;

    if (!obj->oartifact) obj->onamelth = 0;

    save_ocknown = objects[obj->otyp].oc_name_known;
    objects[obj->otyp].oc_name_known = 1;
    save_ocuname = objects[obj->otyp].oc_uname;
    objects[obj->otyp].oc_uname = 0;

    buf = xname(obj);
    if (obj->quan == 1L) buf = obj_is_pname(obj) ? the(buf) : an(buf);

    objects[obj->otyp].oc_name_known = save_ocknown;
    objects[obj->otyp].oc_uname = save_ocuname;
    *obj = save_obj;

    return buf;
}
