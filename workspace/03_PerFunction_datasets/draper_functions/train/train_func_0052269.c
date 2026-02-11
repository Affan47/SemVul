drv_L7_put(int col, int val)
{
    static int cc = -1;


    drv_L7_page(8);

    if (col != cc) {
	cc = col;
	drv_L7_write_ctrl(0x00 | (cc & 0x0f));
	drv_L7_write_ctrl(0x10 | (cc >> 4));
    }
    drv_L7_write_data(val);
    cc++;
}
