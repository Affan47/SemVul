EA65_string (Driver *drvthis, int x, int y, const char string[])
{
        PrivateData *p = (PrivateData *) drvthis->private_data;

        int i;


        x -= 1;
        y -= 1;

        for (i = 0; string[i]; i++) {


                if ((y * p->width) + x + i > (p->width * p->height))
                        break;
                p->framebuf[(y * p->width) + x + i] = string[i];
        }
}
