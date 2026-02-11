main(void)
{
    struct ftdi_context ftdic;
    int f;
    unsigned char buf[1];
    unsigned char bitmask;
    unsigned char input[10];

    if (ftdi_init(&ftdic) < 0)
    {
        fprintf(stderr, "ftdi_init failed\n");
        return EXIT_FAILURE;
    }

    f = ftdi_usb_open(&ftdic, 0x0403, 0x6001);
    if (f < 0 && f != -5)
    {
        fprintf(stderr, "unable to open ftdi device: %d (%s)\n", f, ftdi_get_error_string(&ftdic));
        exit(-1);
    }
    printf("ftdi open succeeded: %d\n",f);

    while (1)
    {

        fgets(input, sizeof(input) - 1, stdin);
        if (input[0] == '\n') break;
        bitmask = strtol(input, NULL, 0);
        printf("Using bitmask 0x%02x\n", bitmask);
        f = ftdi_set_bitmode(&ftdic, bitmask, BITMODE_CBUS);
        if (f < 0)
        {
            fprintf(stderr, "set_bitmode failed for 0x%x, error %d (%s)\n", bitmask, f, ftdi_get_error_string(&ftdic));
            exit(-1);
        }


        f = ftdi_read_pins(&ftdic, &buf[0]);
        if (f < 0)
        {
            fprintf(stderr, "read_pins failed, error %d (%s)\n", f, ftdi_get_error_string(&ftdic));
            exit(-1);
        }
        printf("Read returned 0x%01x\n", buf[0] & 0x0f);
    }
    printf("disabling bitbang mode\n");
    ftdi_disable_bitbang(&ftdic);

    ftdi_usb_close(&ftdic);
    ftdi_deinit(&ftdic);
}
