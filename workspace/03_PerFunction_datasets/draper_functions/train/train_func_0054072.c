open_au(krb5_audit_moddata *auctx)
{
    au_fd = fopen("au.log", "a+");
    if (au_fd == NULL)
        return KRB5_PLUGIN_NO_HANDLE;
    k5_mutex_init(&lock);
    return 0;
}
