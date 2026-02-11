internal_setup(char *str,int *ints)
{
    int i, argc;
    char *cur_str, *argv;

    TRACE2(("internal_setup() str %s ints[0] %d\n",
            str ? str:"NULL", ints ? ints[0]:0));


    if (ints) {
        argc = ints[0];
        if (argc > 0) {
            if (argc > MAXHA)
                argc = MAXHA;
            for (i = 0; i < argc; ++i)
                irq[i] = ints[i+1];
        }
    }


    argv = str;
    while (argv && (cur_str = strchr(argv, ':'))) {
        int val = 0, c = *++cur_str;

        if (c == 'n' || c == 'N')
            val = 0;
        else if (c == 'y' || c == 'Y')
            val = 1;
        else
            val = (int)simple_strtoul(cur_str, NULL, 0);

        if (!strncmp(argv, "disable:", 8))
            disable = val;
        else if (!strncmp(argv, "reserve_mode:", 13))
            reserve_mode = val;
        else if (!strncmp(argv, "reverse_scan:", 13))
            reverse_scan = val;
        else if (!strncmp(argv, "hdr_channel:", 12))
            hdr_channel = val;
        else if (!strncmp(argv, "max_ids:", 8))
            max_ids = val;
        else if (!strncmp(argv, "rescan:", 7))
            rescan = val;
        else if (!strncmp(argv, "shared_access:", 14))
            shared_access = val;
        else if (!strncmp(argv, "probe_eisa_isa:", 15))
            probe_eisa_isa = val;
        else if (!strncmp(argv, "reserve_list:", 13)) {
            reserve_list[0] = val;
            for (i = 1; i < MAX_RES_ARGS; i++) {
                cur_str = strchr(cur_str, ',');
                if (!cur_str)
                    break;
                if (!isdigit((int)*++cur_str)) {
                    --cur_str;
                    break;
                }
                reserve_list[i] =
                    (int)simple_strtoul(cur_str, NULL, 0);
            }
            if (!cur_str)
                break;
            argv = ++cur_str;
            continue;
        }

        if ((argv = strchr(argv, ',')))
            ++argv;
    }
}
