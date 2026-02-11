_cirrus_get_bpp_bytes(void)
{
        unsigned char mode;


        outb(0x07, 0x3c4);
        mode = inb(0x3c5);


        if ((mode & 0x0e) == 0x00) {

                return 1;
        } else if ((mode & 0x0e) == 0x06) {

                return 2;
        } else if ((mode & 0x0e) == 0x04) {

                return 3;
        } else if ((mode & 0x0e) == 0x08) {

                return 4;
        } else {
                dprintf("Cirrus BIOS: FATAL: Unknown mode! ");
                assert(0);
        }
        return 0;
}
