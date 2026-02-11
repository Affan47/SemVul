gncCustomerIsDirty (GncCustomer *cust)
{
    if (!cust) return FALSE;
    return (qof_instance_is_dirty(&cust->inst) ||
            gncAddressIsDirty (cust->addr) ||
            gncAddressIsDirty (cust->shipaddr));
}
