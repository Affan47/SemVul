padline(void)
{
    register int i;

    for (i = 0; i < 12; i++)
        *output_ptr++ = ' ';

    return;
}
