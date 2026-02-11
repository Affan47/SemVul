gnc_invoice_select_search_cb (gpointer start, gpointer isip)
{
    GncISI *isi = isip;

    if (!isi) return NULL;
    g_assert(isi->book);

    return gnc_invoice_search (start,
                               isi->have_owner ? &isi->owner : NULL,
                               isi->book);
}
