setGrub(const char *opt, SdRec *sdr)
{
    FILE *f;
    char *ptr;
    int len, i;
    char line[1000];

    if (!(f = fopen(GRUB_MENU, "r")))
        return errno == ENOENT ? BO_NOMAN : BO_IO;
    for (i = 0; (len = fGets(line, sizeof(line), f)) != -1;)
        if ((ptr = match(line, &len, "title", 5))) {
            if (!strcmp(ptr, opt)) {
                fclose(f);
                sdr->osindex = i;
                sdr->bmstamp = mTime(GRUB_MENU);
                return strDup(&sdr->osname, opt) ? BO_OK : BO_IO;
            }
            i++;
        }
    fclose(f);
    return BO_NOENT;
}
