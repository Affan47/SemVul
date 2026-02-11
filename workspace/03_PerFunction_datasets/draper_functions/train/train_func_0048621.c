PutChar(unsigned char *screendata, int c)
{
    unsigned char *p;

    p = screendata + cur_y * TXT_SCREEN_W * 2 +  cur_x * 2;

    switch (c)
    {
        case '\n':
            NewLine(screendata);
            break;

        case '\b':

            --cur_x;
            if (cur_x < 0)
                cur_x = 0;
            break;

        default:


            p[0] = c;
            p[1] = fgcolor | (bgcolor << 4);

            ++cur_x;

            if (cur_x >= TXT_SCREEN_W)
            {
                NewLine(screendata);
            }

            break;
    }
}
