gncOwnerGetOwnerFromTypeGuid (QofBook *book, GncOwner *owner, QofIdType type, GncGUID *guid)
{
    if (!book || !owner || !type || !guid) return FALSE;

    if (0 == g_strcmp0(type, GNC_ID_CUSTOMER))
    {
        GncCustomer *customer = gncCustomerLookup(book, guid);
        gncOwnerInitCustomer(owner, customer);
        return (NULL != customer);
    }
    else if (0 == g_strcmp0(type, GNC_ID_JOB))
    {
        GncJob *job = gncJobLookup(book, guid);
        gncOwnerInitJob(owner, job);
        return (NULL != job);
    }
    else if (0 == g_strcmp0(type, GNC_ID_VENDOR))
    {
        GncVendor *vendor = gncVendorLookup(book, guid);
        gncOwnerInitVendor(owner, vendor);
        return (NULL != vendor);
    }
    else if (0 == g_strcmp0(type, GNC_ID_EMPLOYEE))
    {
        GncEmployee *employee = gncEmployeeLookup(book, guid);
        gncOwnerInitEmployee(owner, employee);
        return (NULL != employee);
    }
    return 0;
}
