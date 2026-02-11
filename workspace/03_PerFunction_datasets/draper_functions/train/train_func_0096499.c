set_preferred_lft(interface_defn * ifd, char **pparam, int argc UNUSED, char **argv UNUSED)
{
    if (!ifd->real_iface)
        return;
    if (iface_has(":")) {
        char s[] = "0";
        *pparam = realloc(*pparam, sizeof(s));
        if (*pparam == NULL)
            return;
        strcpy(*pparam, s);
    }
}
