Itcl_ParseNamespPath(name, buffer, head, tail)
    CONST char *name;
    Tcl_DString *buffer;
    char **head;
    char **tail;
{
    register char *sep, *newname;

    Tcl_DStringInit(buffer);


    Tcl_DStringAppend(buffer, name, -1);
    newname = Tcl_DStringValue(buffer);

    for (sep=newname; *sep != '\0'; sep++)
        ;

    while (--sep > newname) {
        if (*sep == ':' && *(sep-1) == ':') {
            break;
        }
    }


    if (sep > newname) {
        *tail = sep+1;
        while (sep > newname && *(sep-1) == ':') {
            sep--;
        }
        *sep = '\0';
        *head = newname;
    }


    else {
        *tail = newname;
        *head = NULL;
    }
}
