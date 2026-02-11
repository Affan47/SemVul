identify_pack(int id_limit)
{
    struct obj *obj, *the_obj;
    int n, unid_cnt;

    unid_cnt = 0;
    the_obj = 0;
    for (obj = invent; obj; obj = obj->nobj)
            if (not_fully_identified(obj)) ++unid_cnt, the_obj = obj;

    if (!unid_cnt) {
        You("have already identified all of your possessions.");
    } else if (!id_limit) {

        if (unid_cnt == 1) {
            identify(the_obj);
        } else {


            for (obj = invent; obj; obj = obj->nobj)
                    if (not_fully_identified(obj)) identify(obj);

        }
    } else {

        n = 0;
        if (flags.menu_style == MENU_TRADITIONAL)
                do {
                    n = ggetobj("identify", identify, id_limit, false, (unsigned *)0);
                    if (n < 0) break;
                } while ((id_limit -= n) > 0);
        if (n == 0 || n < -1)
                menu_identify(id_limit);
    }
    update_inventory();
}
