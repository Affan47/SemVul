gncs_get_widget (GNCSearchCoreType *fe)
{
    GtkWidget *toggle, *menu, *box;
    GNCSearchReconciled *fi = (GNCSearchReconciled *)fe;

    g_return_val_if_fail (fi, NULL);
    g_return_val_if_fail (IS_GNCSEARCH_RECONCILED (fi), NULL);

    box = gtk_hbox_new (FALSE, 3);


    menu = make_menu (fe);
    gtk_box_pack_start (GTK_BOX (box), menu, FALSE, FALSE, 3);


    toggle = make_toggle (fi, _("Not Cleared"), CLEARED_NO);
    gtk_box_pack_start (GTK_BOX (box), toggle, FALSE, FALSE, 3);

    toggle = make_toggle (fi, _("Cleared"), CLEARED_CLEARED);
    gtk_box_pack_start (GTK_BOX (box), toggle, FALSE, FALSE, 3);

    toggle = make_toggle (fi, _("Reconciled"), CLEARED_RECONCILED);
    gtk_box_pack_start (GTK_BOX (box), toggle, FALSE, FALSE, 3);

    toggle = make_toggle (fi, _("Frozen"), CLEARED_FROZEN);
    gtk_box_pack_start (GTK_BOX (box), toggle, FALSE, FALSE, 3);

    toggle = make_toggle (fi, _("Voided"), CLEARED_VOIDED);
    gtk_box_pack_start (GTK_BOX (box), toggle, FALSE, FALSE, 3);


    return box;
}
