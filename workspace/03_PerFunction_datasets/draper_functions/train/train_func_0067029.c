print_ole2_property(property_t * property)
{
    char            spam[128], *buf;

    if (property->name_size > 64) {
        cli_dbgmsg("[err name len: %d]\n", property->name_size);
        return;
    }
    buf = get_property_name(property->name, property->name_size);
    snprintf(spam, sizeof(spam), "OLE2: %s ", buf ? buf : "<noname>");
    spam[sizeof(spam) - 1] = '\0';
    if (buf)
        free(buf);
    switch (property->type) {
    case 2:
        strncat(spam, " [file] ", sizeof(spam) - 1 - strlen(spam));
        break;
    case 1:
        strncat(spam, " [dir ] ", sizeof(spam) - 1 - strlen(spam));
        break;
    case 5:
        strncat(spam, " [root] ", sizeof(spam) - 1 - strlen(spam));
        break;
    default:
        strncat(spam, " [unkn] ", sizeof(spam) - 1 - strlen(spam));
    }
    spam[sizeof(spam) - 1] = '\0';
    switch (property->color) {
    case 0:
        strncat(spam, " r  ", sizeof(spam) - 1 - strlen(spam));
        break;
    case 1:
        strncat(spam, " b  ", sizeof(spam) - 1 - strlen(spam));
        break;
    default:
        strncat(spam, " u  ", sizeof(spam) - 1 - strlen(spam));
    }
    spam[sizeof(spam) - 1] = '\0';
    cli_dbgmsg("%s size:0x%.8x flags:0x%.8x\n", spam, property->size, property->user_flags);
}
