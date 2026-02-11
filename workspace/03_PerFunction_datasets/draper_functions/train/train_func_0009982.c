sp_unit_selector_remove_adjustment(SPUnitSelector *us, GtkAdjustment *adj)
{
    g_return_if_fail(us != NULL);
    g_return_if_fail(SP_IS_UNIT_SELECTOR(us));
    g_return_if_fail(adj != NULL);
    g_return_if_fail(GTK_IS_ADJUSTMENT(adj));

    g_return_if_fail(g_slist_find(us->adjustments, adj));

    us->adjustments = g_slist_remove(us->adjustments, adj);
    gtk_object_unref(GTK_OBJECT(adj));
}
