httpRemoveUserFromGroup(HttpGroup *gp, cchar *user)
{
    char    *name;
    int     next;

    for (next = 0; (name = mprGetNextItem(gp->users, &next)) != 0; ) {
        if (strcmp(name, user) == 0) {
            mprRemoveItem(gp->users, name);
            return 0;
        }
    }
    return MPR_ERR_CANT_ACCESS;
}
