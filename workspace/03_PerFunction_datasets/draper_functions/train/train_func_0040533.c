main(int argc, char **argv)
{
    Octstr *headers;
    List *expected;
    List *split;
    Octstr *packed;
    List *unpacked;
    Octstr *filename;
    long i;
    int mptr;

    gwlib_init();
    wsp_strings_init();

    mptr = get_and_set_debugs(argc, argv, NULL);
    if (argc - mptr <= 0)
        panic(0, "Usage: test_headers [options] header-file");

    filename = octstr_create(argv[mptr]);
    headers = octstr_read_file(octstr_get_cstr(filename));
    split_headers(headers, &split, &expected);
    packed = wsp_headers_pack(split, 0, WSP_1_2);
    unpacked = wsp_headers_unpack(packed, 0);

    if (gwlist_len(unpacked) != gwlist_len(expected)) {
        error(0, "Expected %ld headers, generated %ld.\n",
              gwlist_len(expected), gwlist_len(unpacked));
    } else {
        for (i = 0; i < gwlist_len(unpacked); i++) {
            Octstr *got, *exp;
            got = gwlist_get(unpacked, i);
            exp = gwlist_get(expected, i);
            if (octstr_compare(got, exp) != 0) {
                error(0, "Exp: %s", octstr_get_cstr(exp));
                error(0, "Got: %s", octstr_get_cstr(got));
            }
        }
    }

    test_header_combine();

    octstr_destroy(headers);
    octstr_destroy(filename);
    gwlist_destroy(split, octstr_destroy_item);
    gwlist_destroy(expected, octstr_destroy_item);
    octstr_destroy(packed);
    gwlist_destroy(unpacked, octstr_destroy_item);

    wsp_strings_shutdown();
    gwlib_shutdown();
    return 0;
}
