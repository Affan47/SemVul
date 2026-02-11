tax_table_delete_table_cb (GtkButton *button, TaxTableWindow *ttw)
{
    g_return_if_fail (ttw);

    if (!ttw->current_table)
        return;

    if (gncTaxTableGetRefcount (ttw->current_table) > 0)
    {
        char *message =
            g_strdup_printf (_("Tax table \"%s\" is in use. You cannot delete it."),
                             gncTaxTableGetName (ttw->current_table));
        gnc_error_dialog (ttw->dialog, "%s", message);
        g_free (message);
        return;
    }

    if (gnc_verify_dialog (ttw->dialog, FALSE,
                           _("Are you sure you want to delete \"%s\"?"),
                           gncTaxTableGetName (ttw->current_table)))
    {

        gnc_suspend_gui_refresh ();
        gncTaxTableBeginEdit (ttw->current_table);
        gncTaxTableDestroy (ttw->current_table);
        ttw->current_table = NULL;
        ttw->current_entry = NULL;
        gnc_resume_gui_refresh ();
    }
}
