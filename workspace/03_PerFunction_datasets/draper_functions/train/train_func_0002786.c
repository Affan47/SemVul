sed1520_string(Driver * drvthis, int x, int y, const char string[])
{
    PrivateData *p = drvthis->private_data;
    int i;

    x--;
    y--;

    for (i = 0; string[i] != '\0'; i++)
	drawchar2fb(p->framebuf, x + i, y, string[i]);
}
