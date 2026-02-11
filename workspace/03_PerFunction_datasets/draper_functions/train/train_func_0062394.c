oname(struct obj *obj, const char *name)
{
    int lth;
    char buf[PL_PSIZ];

    lth = *name ? (int)(strlen(name) + 1) : 0;
    if (lth > PL_PSIZ) {
        lth = PL_PSIZ;
        name = strncpy(buf, name, PL_PSIZ - 1);
        buf[PL_PSIZ - 1] = '\0';
    }


    if (obj->oartifact || (lth && exist_artifact(obj->otyp, name)))
            return obj;

    if (lth == obj->onamelth) {

        if (lth) strcpy(ONAME(obj), name);
    } else {
        obj = realloc_obj(obj, obj->oxlth,
                          (void *)obj->oextra, lth, name);
    }
    if (lth) artifact_exists(obj, name, true);
    if (obj->oartifact) {

        if (obj == uswapwep) untwoweapon();

        if (obj == uwep) set_artifact_intrinsic(obj, true, W_WEP);
    }
    if (carried(obj)) update_inventory();
    return obj;
}
