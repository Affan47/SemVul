gncInvoiceAutoApplyPayments (GncInvoice *invoice)
{
    GNCLot *inv_lot;
    Account *acct;
    const GncOwner *owner;
    GList *lot_list;
    struct lotmatch lm;


    g_return_if_fail (invoice);
    g_return_if_fail (invoice->posted_lot);

    inv_lot = invoice->posted_lot;
    acct = invoice->posted_acc;
    owner = gncOwnerGetEndOwner (gncInvoiceGetOwner (invoice));


    lm.positive_balance =  gnc_numeric_positive_p (gnc_lot_get_balance (inv_lot));
    lm.owner = owner;
    lot_list = xaccAccountFindOpenLots (acct, gnc_lot_match_owner_balancing,
                                        &lm, NULL);

    lot_list = g_list_prepend (lot_list, inv_lot);
    gncOwnerAutoApplyPaymentsWithLots (owner, lot_list);
    g_list_free (lot_list);
}
