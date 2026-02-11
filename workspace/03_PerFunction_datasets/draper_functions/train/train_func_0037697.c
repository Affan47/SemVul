bt_get_parent( gpointer pObject )
{
    const GncTaxTable* tt;
    const GncTaxTable* pParent;
    const GncGUID* parent_guid;

    g_return_val_if_fail( pObject != NULL, NULL );
    g_return_val_if_fail( GNC_IS_TAXTABLE(pObject), NULL );

    tt = GNC_TAXTABLE(pObject);
    pParent = gncTaxTableGetParent( tt );
    if ( pParent == NULL )
    {
        parent_guid = NULL;
    }
    else
    {
        parent_guid = qof_instance_get_guid( QOF_INSTANCE(pParent) );
    }

    return (gpointer)parent_guid;
}
