var_set(char *id, interface_defn * ifd)
{
    char *varvalue;

    varvalue = get_var(id, strlen(id), ifd);
    if (varvalue) {
        free(varvalue);
        return 1;
    } else {
        return 0;
    }
}
