dothrow(void)
{
    struct obj *obj;
    int shotlimit;


    shotlimit = (multi || save_cm) ? multi + 1 : 0;
    multi = 0;

    if (notake(youmonst.data)) {
        You("are physically incapable of throwing anything.");
        return 0;
    }

    if(check_capacity((char *)0)) return(0);
    obj = getobj(uslinging() ? bullets : toss_objs, "throw");


    if (!obj) return(0);
    return throw_obj(obj, shotlimit);
}
