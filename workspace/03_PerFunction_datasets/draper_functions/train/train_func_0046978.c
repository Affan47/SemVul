fourinsix(struct sockaddr_storage *v6)
{
    struct sockaddr_storage v4;

    if (v6ready == 0 || STORAGE_FAMILY(*v6) != AF_INET6 ||
        IN6_IS_ADDR_V4MAPPED(&STORAGE_SIN_ADDR6_NF(*v6)) == 0) {
        return;
    }
    memset(&v4, 0, sizeof v4);
    STORAGE_FAMILY(v4) = AF_INET;
    memcpy(&STORAGE_SIN_ADDR(v4),
           (unsigned char *) &STORAGE_SIN_ADDR6(*v6) + 12,
           sizeof STORAGE_SIN_ADDR(v4));
    STORAGE_PORT(v4) = STORAGE_PORT6(*v6);
    SET_STORAGE_LEN(v4, sizeof(struct sockaddr_in));
    *v6 = v4;
}
