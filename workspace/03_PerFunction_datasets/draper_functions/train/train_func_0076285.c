switch_ext (char *targ, const char *src, const char *ext)
{
    int i = gretl_dotpos(src);

    if (targ != src) {
        strncpy(targ, src, i);
    }

    targ[i] = '.';
    targ[i + 1] = 0;
    strcat(targ, ext);

    return targ;
}
