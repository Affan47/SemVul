display_minventory(struct monst *mon, int dflags, char *title)
{
    struct obj *ret;
    struct obj m_gold;
    char tmp[QBUFSZ];
    int n;
    menu_item *selected = 0;
    int do_all = (dflags & MINV_ALL) != 0,
        do_gold = (do_all && mon->mgold);

    sprintf(tmp,"%s %s:", s_suffix(noit_Monnam(mon)),
            do_all ? "possessions" : "armament");
    if (do_all ? (mon->minvent || mon->mgold)
        : (mon->misc_worn_check || MON_WEP(mon))) {


        youmonst.data = mon->data;
        if (do_gold) {


            m_gold = zeroobj;
            m_gold.otyp = GOLD_PIECE;  m_gold.oclass = COIN_CLASS;
            m_gold.quan = mon->mgold;  m_gold.dknown = 1;
            m_gold.where = OBJ_FREE;

            if (add_to_minv(mon, &m_gold))
                    panic("display_minventory: static object freed.");
        }
        n = query_objlist(title ? title : tmp, mon->minvent, INVORDER_SORT, &selected,
                          (dflags & MINV_NOLET) ? PICK_NONE : PICK_ONE,
                          do_all ? allow_all : worn_wield_only);
        if (do_gold) obj_extract_self(&m_gold);
        set_uasmon();
    }
    else
    {
        invdisp_nothing(title ? title : tmp, "(none)");
        n = 0;
    }

    if (n > 0)
    {
        ret = selected[0].item.a_obj;
        free(selected);


        if (ret == &m_gold) ret = NULL;
    }
    else
    {
        ret = NULL;
    }
    return ret;
}
