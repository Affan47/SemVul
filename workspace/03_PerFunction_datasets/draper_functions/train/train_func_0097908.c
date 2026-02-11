gnc_customer_window_destroy_cb (GtkWidget *widget, gpointer data)
{
    CustomerWindow *cw = data;
    GncCustomer *customer = cw_get_customer (cw);

    gnc_suspend_gui_refresh ();

    if (cw->dialog_type == NEW_CUSTOMER && customer != NULL)
    {
        gncCustomerBeginEdit (customer);
        gncCustomerDestroy (customer);
        cw->customer_guid = *guid_null ();
    }

    if (cw->addrX_selection_source_id)
        g_source_remove (cw->addrX_selection_source_id);

    gnc_unregister_gui_component (cw->component_id);
    gnc_resume_gui_refresh ();

    g_free (cw);
}
