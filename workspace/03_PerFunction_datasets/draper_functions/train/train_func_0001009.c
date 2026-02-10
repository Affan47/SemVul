gncVendorCreate (QofBook *book)
{
    GncVendor *vendor;

    if (!book) return NULL;

    vendor = g_object_new (GNC_TYPE_VENDOR, NULL);
    qof_instance_init_data (&vendor->inst, _GNC_MOD_NAME, book);

    vendor->id = CACHE_INSERT ("");
    vendor->name = CACHE_INSERT ("");
    vendor->notes = CACHE_INSERT ("");
    vendor->addr = gncAddressCreate (book, &vendor->inst);
    vendor->taxincluded = GNC_TAXINCLUDED_USEGLOBAL;
    vendor->active = TRUE;
    vendor->jobs = NULL;

    if (gs_address_event_handler_id == 0)
    {
        gs_address_event_handler_id = qof_event_register_handler(listen_for_address_events, NULL);
    }

    qof_event_gen (&vendor->inst, QOF_EVENT_CREATE, NULL);

    return vendor;
}
