drv_BuE_MT_defchar(const int ascii, const unsigned char *matrix)
{
    int i;
    char cmd[22] = ESC "&T";

    cmd[3] = '\0';
    cmd[4] = 0x40 | 8 * ascii;

    for (i = 0; i < 8; i++) {
	cmd[2 * i + 5] = '\1';
	cmd[2 * i + 6] = matrix[i] & 0x1f;
    }
    cmd[21] = '\377';

    drv_generic_serial_write(cmd, 22);
}
