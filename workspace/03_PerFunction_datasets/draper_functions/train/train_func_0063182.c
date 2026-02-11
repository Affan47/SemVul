httpAddUsersToGroup(HttpAuth *auth, cchar *group, cchar *userList)
{
    HttpGroup   *gp;
    char        *user, *users, *tok;

    gp = 0;

    if (auth->groups == 0 || (gp = (HttpGroup*) mprLookupKey(auth->groups, group)) == 0) {
        return MPR_ERR_CANT_ACCESS;
    }
    tok = NULL;
    users = sclone(userList);
    user = stok(users, " ,\t", &tok);
    while (user) {

        httpAddUserToGroup(auth, gp, user);
        user = stok(NULL, " \t", &tok);
    }
    return 0;
}
