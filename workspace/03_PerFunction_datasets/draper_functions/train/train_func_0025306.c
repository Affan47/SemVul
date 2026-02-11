printFloat(float f, pf print, void *info, int space)
{
    char buf[128];

    if (space)
	sprintf(buf, " %.02f", f);
    else
	sprintf(buf, "%.02f", f);
    trim (buf);
    print(buf, info);
}
