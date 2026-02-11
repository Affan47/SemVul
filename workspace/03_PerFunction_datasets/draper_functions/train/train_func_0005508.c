AppendV4AddrsToHostent(
    struct hostent *from,
    char **buf,
    PRIntn *bufsize,
    PRHostEnt *to)
{
    PRIntn na, na_old;
    char **ap;
    char **new_addr_list;


    for (na_old = 0, ap = to->h_addr_list; *ap != 0; na_old++, ap++)
        {;}
    for (na = na_old + 1, ap = from->h_addr_list; *ap != 0; na++, ap++)
        {;}
    new_addr_list = (char**)Alloc(
        na * sizeof(char*), buf, bufsize, sizeof(char**));
    if (!new_addr_list) return PR_FAILURE;


    for (na = 0, ap = to->h_addr_list; *ap != 0; na++, ap++) {
        new_addr_list[na] = to->h_addr_list[na];
    }
    to->h_addr_list = new_addr_list;


    for (ap = from->h_addr_list; *ap != 0; na++, ap++) {
        to->h_addr_list[na] = Alloc(to->h_length, buf, bufsize, 0);
        if (!to->h_addr_list[na]) return PR_FAILURE;
        MakeIPv4MappedAddr(*ap, to->h_addr_list[na]);
    }
    to->h_addr_list[na] = 0;
    return PR_SUCCESS;
}
