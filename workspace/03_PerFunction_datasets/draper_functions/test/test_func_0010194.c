print_key(kdbe_key_t *k)
{
    unsigned int i;
    utf8str_t *str;

    printf("\t\t\tver: %d\n", k->k_ver);

    printf("\t\t\tkvno: %d\n", k->k_kvno);

    for (i = 0; i < k->k_enctype.k_enctype_len; i++) {
        printf("\t\t\tenc type: 0x%x\n",
               k->k_enctype.k_enctype_val[i]);
    }

    str = k->k_contents.k_contents_val;
    for (i = 0; i < k->k_contents.k_contents_len; i++, str++) {
        print_hex("key", str);
    }
}
