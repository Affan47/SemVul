sreadHeaderSpix(const l_uint32  *data,
                l_int32         *pwidth,
                l_int32         *pheight,
                l_int32         *pbps,
                l_int32         *pspp,
                l_int32         *piscmap)
{
char    *id;
l_int32  d, ncolors;

    PROCNAME("sreadHeaderSpix");

    if (!data)
        return ERROR_INT("data not defined", procName, 1);
    if (!pwidth || !pheight || !pbps || !pspp)
        return ERROR_INT("input ptr(s) not defined", procName, 1);
    *pwidth = *pheight = *pbps = *pspp = 0;
    if (piscmap)
      *piscmap = 0;


    id = (char *)data;
    if (id[0] != 's' || id[1] != 'p' || id[2] != 'i' || id[3] != 'x')
        return ERROR_INT("not a valid spix file", procName, 1);

    *pwidth = data[1];
    *pheight = data[2];
    d = data[3];
    if (d <= 16) {
      *pbps = d;
      *pspp = 1;
    }
    else {
      *pbps = 8;
      *pspp = d / 8;
    }
    ncolors = data[5];
    if (piscmap)
        *piscmap = (ncolors == 0) ? 0 : 1;

    return 0;
}
