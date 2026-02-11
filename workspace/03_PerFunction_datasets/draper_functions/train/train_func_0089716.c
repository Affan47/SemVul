drv_CF_defchar23(const int ascii, const unsigned char *matrix)
{
    int i;
    unsigned char buffer[9];


    buffer[0] = (char) (ascii - CHAR0);


    for (i = 0; i < 8; i++) {
	buffer[i + 1] = matrix[i] & 0x3f;
    }

    drv_CF_send(9, 9, buffer);
}
