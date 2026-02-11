gv_get_last_vect(void)
{
    geovect *lv;

    if (!Vect_top) {
	return (NULL);
    }

    for (lv = Vect_top; lv->next; lv = lv->next) ;

    G_debug(5, "gv_get_last_vect(): id=%d", lv->gvect_id);

    return (lv);
}
