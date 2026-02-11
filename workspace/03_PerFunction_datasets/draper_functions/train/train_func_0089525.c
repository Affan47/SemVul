gnc_price_unref(GNCPrice *p)
{
    if (!p) return;
    if (p->refcount == 0)
    {
        return;
    }

    p->refcount--;

    if (p->refcount <= 0)
    {
        if (NULL != p->db)
        {
            PERR("last unref while price in database");
        }
        gnc_price_destroy (p);
    }
}
