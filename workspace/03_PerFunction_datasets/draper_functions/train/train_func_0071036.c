gncCustomerSetTerms (GncCustomer *cust, GncBillTerm *terms)
{
    if (!cust) return;
    if (cust->terms == terms) return;

    gncCustomerBeginEdit (cust);
    if (cust->terms)
        gncBillTermDecRef (cust->terms);
    cust->terms = terms;
    if (cust->terms)
        gncBillTermIncRef (cust->terms);
    mark_customer (cust);
    gncCustomerCommitEdit (cust);
}
