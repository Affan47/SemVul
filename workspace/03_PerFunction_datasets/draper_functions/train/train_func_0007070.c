gx_build_blended_image_row(byte *buf_ptr, int y, int planestride,
                           int width, int num_comp, byte bg, byte *linebuf)
{
    int x;
    for (x = 0; x < width; x++) {
        byte comp, a;
        int tmp, comp_num;


        a = buf_ptr[x + planestride * num_comp];

        if ((a + 1) & 0xfe) {
            a ^= 0xff;
            for (comp_num = 0; comp_num < num_comp; comp_num++) {
                comp  = buf_ptr[x + planestride * comp_num];
                tmp = ((bg - comp) * a) + 0x80;
                comp += (tmp + (tmp >> 8)) >> 8;
                linebuf[x * num_comp + comp_num] = comp;
            }
        } else if (a == 0) {
            for (comp_num = 0; comp_num < num_comp; comp_num++) {
                linebuf[x * num_comp + comp_num] = bg;
            }
        } else {
            for (comp_num = 0; comp_num < num_comp; comp_num++) {
                comp = buf_ptr[x + planestride * comp_num];
                linebuf[x * num_comp + comp_num] = comp;
            }
        }
    }
}
