makeValTabSG8(void)
{
l_int32   i;
l_uint8  *tab;

    PROCNAME("makeValTabSG8");

    if ((tab = (l_uint8 *)CALLOC(65, sizeof(l_uint8))) == NULL)
        return (l_uint8 *)ERROR_PTR("calloc fail for tab", procName, NULL);

    for (i = 0; i < 65; i++)
        tab[i] = 0xff - (i * 255) / 64;

    return tab;
}
