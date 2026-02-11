_dxf_BuildInstanceNumString(int instance)
{
    static char localstr[10];
    char *tail = localstr;
    int np;

    if (instance < 0 || instance > 999)
    {


        sprintf(tail, "%d", instance);
        tail += strlen(tail);
    }
    else if (instance > 99)
    {
       np = instance / 100;
       *(tail++) = np + '0';
       instance -= np * 100;
       np = instance / 10;
       *(tail++) = np + '0';
       instance -= np * 10;
       *(tail++) = instance + '0';
    }
    else if (instance > 9)
    {
       np = instance / 10;
       *(tail++) = np + '0';
       instance -= np * 10;
       *(tail++) = instance + '0';
    }
    else
       *(tail++) = instance + '0';
    *(tail) = '\0';

    return localstr;
}
