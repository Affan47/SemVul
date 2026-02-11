xdmGetAuthHelper(unsigned short namelen, const char *name, int nbytes)
{
    Xauth *new;

    if (!(new = generateAuthHelper(namelen, name, nbytes)))
        return 0;


    ((char *)new->data)[new->data_length - 8] = '\0';
    debug("local server auth %02[*hhx\n", new->data_length, new->data);
    return new;
}
