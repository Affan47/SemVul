drv_FutabaVFD_write(const int row, const int col, const char *data, int len)
{
    unsigned char oldPos = curPos;
    if (curOn)
	drv_FutabaVFD_showCursor(0);
    drv_FutabaVFD_goto(row * DCOLS + col);
    drv_FutabaVFD_send(data, len);
    drv_FutabaVFD_goto(oldPos);
    if (curOn)
	drv_FutabaVFD_showCursor(1);
}
