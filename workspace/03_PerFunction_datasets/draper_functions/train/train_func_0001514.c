r_short(RFILE *p)
{
    short x = -1;
    unsigned char *buffer;

    buffer = (unsigned char *) r_string(2, p);
    if (buffer != NULL) {
        x = buffer[0];
        x |= buffer[1] << 8;

        x |= -(x & 0x8000);
    }
    return x;
}
