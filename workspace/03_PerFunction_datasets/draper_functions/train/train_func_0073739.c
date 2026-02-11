read_wizkit(void)
{
    FILE *fp;
    char *ep, buf[BUFSZ];
    struct obj *otmp;
    bool bad_items = false, skip = false;

    if (!wizard || !(fp = fopen_wizkit_file())) return;

    while (fgets(buf, (int)(sizeof buf), fp))
    {
        ep = index(buf, '\n');
        if (skip)
        {
            if (ep) skip = false;
        }
        else
        {
            if (!ep) skip = true;
            else *ep = '\0';

            if (buf[0])
            {
                otmp = readobjnam(buf, (struct obj *)0, false);
                if (otmp)
                {
                    if (otmp != &zeroobj)
                            otmp = addinv(otmp);
                }
                else
                {

                    raw_printf("Bad wizkit item: \"%.60s\"", buf);
                    bad_items = true;
                }
            }
        }
    }
    if (bad_items)
            wait_synch();
    fclose(fp);
    return;
}
