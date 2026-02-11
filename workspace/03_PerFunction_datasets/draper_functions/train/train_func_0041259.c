read_code (FILE * file, unsigned char *buf, int *bit_pos, int bit_size)
{
    int i;
    int code = 0;
    int pos = 1;

    for (i = 0; i < bit_size; i++)
    {
        int byte_pos = (*bit_pos >> 3) & 255;

        if (byte_pos == 0)
        {
            int data_len = fgetc (file);

            if (data_len == 0)
            {


                return -1;
            }
            fread (buf + 256 - data_len, 1, data_len, file);
            byte_pos = 256 - data_len;
            *bit_pos = byte_pos << 3;
        }
        if (buf[byte_pos] & (1 << (*bit_pos & 7)))
            code += pos;
        pos += pos;
        (*bit_pos)++;
    }
    return code;
}
