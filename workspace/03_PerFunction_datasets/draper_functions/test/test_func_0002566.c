noteXSession(struct display *di, struct display *d, void *ctx)
{
    AULData *dt = (AULData *)ctx;
    (void)d;

    if (di->status == remoteLogin || di->userSess != dt->uid)
        dt->any = True;
}
