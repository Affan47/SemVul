upd_hiddenusers(Entry *ce, Section *cs)
{
    char *nv;
    const char *msu, *pt, *et;
    struct passwd *pw;
    unsigned minuid, maxuid;
    char nbuf[128];

    if (!ce->active)
        return;

    msu = getFqVal(cs->name, "MinShowUID", "0");
    sscanf(msu, "%u", &minuid);
    msu = getFqVal(cs->name, "MaxShowUID", "65535");
    sscanf(msu, "%u", &maxuid);

    nv = 0;
    pt = ce->value;
    for (;;) {
        et = strpbrk(pt, ";,");
        if (et) {
            memcpy(nbuf, pt, et - pt);
            nbuf[et - pt] = 0;
        } else {
            strcpy(nbuf, pt);
        }
        if ((pw = getpwnam(nbuf))) {
            if (!pw->pw_uid ||
                (pw->pw_uid >= minuid && pw->pw_uid <= maxuid))
            {
                if (nv)
                    strCat(&nv, ",%s", nbuf);
                else
                    nv = mstrdup(nbuf);
            }
        }
        if (!et)
            break;
        pt = et + 1;
    }
    ce->value = nv ? nv : "";
}
