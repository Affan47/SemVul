createUser(cchar *realm, cchar *name, cchar *password, bool enabled)
{
    User    *up;

    if ((up = mprAllocObj(User, manageUser)) != 0) {
        up->realm = sclone(realm);
        up->name = sclone(name);
        up->password = sclone(password);
        up->enabled = enabled;
    }
    return up;
}
