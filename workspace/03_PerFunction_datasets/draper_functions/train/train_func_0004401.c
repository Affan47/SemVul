sum_row_black_and_white(byte *row, int32 x1, int32 x2)
{
    int sum = 0, x, n = x2 - x1;
    byte *p = row + x1;
    for (x = 0; x <= n; x++) if (p[x]) sum++;
    return sum;
}
