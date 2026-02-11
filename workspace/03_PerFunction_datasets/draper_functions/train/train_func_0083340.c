gncInvoiceCreate (QofBook *book)
{
    GncInvoice *invoice;

    if (!book) return NULL;

    invoice = g_object_new (GNC_TYPE_INVOICE, NULL);
    qof_instance_init_data (&invoice->inst, _GNC_MOD_NAME, book);

    invoice->id = CACHE_INSERT ("");
    invoice->notes = CACHE_INSERT ("");
    invoice->billing_id = CACHE_INSERT ("");

    invoice->billto.type = GNC_OWNER_CUSTOMER;
    invoice->active = TRUE;

    invoice->to_charge_amount = gnc_numeric_zero();

    qof_event_gen (&invoice->inst, QOF_EVENT_CREATE, NULL);

    return invoice;
}
