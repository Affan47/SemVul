setAuthorization(struct display *d)
{
    register Xauth **auth = d->authorizations;
    int i;

    for (i = 0; i < d->authNum; i++) {
        if (auth[i]->name_length == 9 &&
                !memcmp(auth[i]->name, "SUN-DES-1", 9))
            continue;
        if (auth[i]->name_length == 14 &&
                !memcmp(auth[i]->name, "MIT-KERBEROS-5", 14))
            continue;
        XSetAuthorization(auth[i]->name, (int)auth[i]->name_length,
                          auth[i]->data, (int)auth[i]->data_length);
    }
}
