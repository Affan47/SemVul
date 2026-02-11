print_tldata(kdbe_tl_t *tldata, int len)
{
    int i;

    printf("\t\t\titems: %d\n", len);

    for (i = 0; i < len; i++, tldata++) {
        print_tl(tldata);
    }
}
