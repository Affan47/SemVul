read_u32(NYTP_file ifile)
{
    unsigned char d;
    U32 newint;

    NYTP_read(ifile, &d, sizeof(d), "integer prefix");

    if (d < 0x80) {
        newint = d;
    }
    else {
        unsigned char buffer[4];
        unsigned char *p = buffer;
        unsigned int length;

        if (d < 0xC0) {
            newint = d & 0x7F;
            length = 1;
        }
        else if (d < 0xE0) {
            newint = d & 0x1F;
            length = 2;
        }
        else if (d < 0xFF) {
            newint = d & 0xF;
            length = 3;
        }
        else {
            newint = 0;
            length = 4;
        }
        NYTP_read(ifile, buffer, length, "integer");
        while (length--) {
            newint <<= 8;
            newint |= *p++;
        }
    }
    return newint;
}
