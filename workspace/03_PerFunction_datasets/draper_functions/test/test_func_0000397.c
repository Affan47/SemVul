gnc_price_set_currency(GNCPrice *p, gnc_commodity *c)
{
    if (!p) return;

    if (!gnc_commodity_equiv(p->currency, c))
    {


        gnc_price_ref (p);
        remove_price (p->db, p, TRUE);
        gnc_price_begin_edit (p);
        p->currency = c;
        gnc_price_set_dirty(p);
        gnc_price_commit_edit (p);
        add_price (p->db, p);
        gnc_price_unref (p);
    }
}
