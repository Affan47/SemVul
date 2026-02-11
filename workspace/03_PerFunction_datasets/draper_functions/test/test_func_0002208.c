vxlan_print(const u_char *bp, u_int len)
{
    u_int8_t flags;
    u_int32_t vni;

    if (len < 8) {
        printf("[|VXLAN]");
        return;
    }

    flags = *bp;
    bp += 4;

    vni = EXTRACT_24BITS(bp);
    bp += 4;

    printf("VXLAN, ");

    fputs("flags [", stdout);
    if (flags & 0x08)
        fputs("I", stdout);
    else
        fputs(".", stdout);
    fputs("] ", stdout);

    printf("(0x%02x), ", flags);
    printf("vni %u\n", vni);

    ether_print(gndo, bp, len - 8, len - 8, NULL, NULL);
    return;
}
