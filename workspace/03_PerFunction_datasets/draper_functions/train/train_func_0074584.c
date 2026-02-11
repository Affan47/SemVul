lock()
{
    if (locked)
	return (false);
    uid_t ouid = geteuid();
    seteuid(0);
    bool ok = create();
    if (!ok)
	ok = check() && create();
    seteuid(ouid);
    return (ok);
}
