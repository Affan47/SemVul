gnc_invoice_select_create (GtkWidget *hbox, QofBook *book,
                                       const GncOwner *owner,
                                       GncInvoice *invoice,
                                       GtkWidget *label)
{
    GtkWidget *edit;
    GncISI *isi;

    g_return_val_if_fail (hbox != NULL, NULL);
    g_return_val_if_fail (book != NULL, NULL);


    isi = g_new0(GncISI, 1);
    if (!isi)
        return NULL;

    if (owner)
    {
        gncOwnerCopy(owner, &isi->owner);
        isi->have_owner = TRUE;
    }
    else
    {
        gncOwnerInitCustomer(&isi->owner, NULL);
    }
    isi->book = book;
    isi->label = label;

    edit = gnc_general_search_new (GNC_INVOICE_MODULE_NAME, _("Select..."),
                                   TRUE, gnc_invoice_select_search_cb, isi, isi->book);
    if (!edit)
    {
        g_free(isi);
        return NULL;
    }

    gnc_general_search_set_selected (GNC_GENERAL_SEARCH (edit), invoice);
    gtk_box_pack_start (GTK_BOX (hbox), edit, FALSE, FALSE, 0);
    g_object_set_data_full(G_OBJECT(edit), "isi-state", isi, g_free);


    gnc_invoice_select_search_set_label(isi);

    return edit;
}
