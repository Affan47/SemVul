gncOwnerGetAccountTypesList (const GncOwner *owner)
{
    g_return_val_if_fail (owner, NULL);

    switch (gncOwnerGetType (owner))
    {
    case GNC_OWNER_CUSTOMER:
        return (g_list_prepend (NULL, (gpointer)ACCT_TYPE_RECEIVABLE));
    case GNC_OWNER_VENDOR:
    case GNC_OWNER_EMPLOYEE:
        return (g_list_prepend (NULL, (gpointer)ACCT_TYPE_PAYABLE));
        break;
    default:
        return (g_list_prepend (NULL, (gpointer)ACCT_TYPE_NONE));
    }
}
