_config_startElement(void *arg, const char *name, const char **atts)
{
    struct build_data *bd = (struct build_data *) arg;
    int i = 0;

    nad_append_elem(bd->nad, -1, (char *) name, bd->depth);
    while(atts[i] != NULL)
    {
        nad_append_attr(bd->nad, -1, (char *) atts[i], (char *) atts[i + 1]);
        i += 2;
    }

    bd->depth++;
}
