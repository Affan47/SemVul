main(int argc, char **argv)
{
    Octstr *data, *filename, *hex;

    gwlib_init();

    get_and_set_debugs(argc, argv, NULL);

    if (argc < 2)
        panic(0, "Syntax: %s <file>\n", argv[0]);

    filename = octstr_create(argv[1]);
    data = octstr_read_file(octstr_get_cstr(filename));

    if (data == NULL)
        panic(0, "Cannot read file.");


    hex = octstr_duplicate(data);
    octstr_strip_crlfs(hex);
    if (octstr_is_all_hex(hex)) {
        debug("",0,"Trying to converting from hex to binary.");
        if (octstr_hex_to_binary(hex) == 0) {
            FILE *f = fopen(argv[2], "w");
            debug("",0,"Convertion was successfull. Writing binary content to file `%s'",
                  argv[2]);
            octstr_destroy(data);
            data = octstr_duplicate(hex);
            octstr_print(f, data);
            fclose(f);
        } else {
            debug("",0,"Failed to convert from hex?!");
        }
    }

    debug("",0,"Dumping file `%s':", octstr_get_cstr(filename));
    octstr_dump(data, 0);

    octstr_destroy(data);
    octstr_destroy(hex);
    gwlib_shutdown();
    return 0;
}
