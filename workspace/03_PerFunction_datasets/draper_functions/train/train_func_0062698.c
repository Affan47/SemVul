tab_lookup(struct cvt_tab *tab, int c)
{
    for (; tab->in1 > 0; tab++)
        if (tab->in1 == c)
            return tab;
    return NULL;
}
