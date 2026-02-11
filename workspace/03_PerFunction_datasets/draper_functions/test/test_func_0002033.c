xconf_new_from_file(gchar *fname, gchar *name)
{
    FILE *fp = fopen(fname, "r");
    xconf *ret = NULL;
    if (fp)
    {
        ret = read_block(fp, name);
        fclose(fp);
    }

    return ret;
}
