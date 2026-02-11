invoice_should_be_saved( GncInvoice *invoice )
{
    const char *id;

    g_return_val_if_fail( invoice != NULL, FALSE );


    id = gncInvoiceGetID( invoice );
    if ( id == NULL || *id == '\0' )
    {
        return FALSE;
    }

    return TRUE;
}
