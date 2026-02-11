can_execute(const char *pathname)
{
    struct stat     st;
    explain_have_identity_t hid;

    if (stat(pathname, &st) < 0)
        return 0;
    explain_have_identity_init(&hid);
    errno = EACCES;
    return explain_have_execute_permission(&st, &hid);
}
