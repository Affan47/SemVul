createMatrix2dScale(l_float32  scalex,
                    l_float32  scaley)
{
l_float32  *mat;

    PROCNAME("createMatrix2dScale");

    if ((mat = (l_float32 *)CALLOC(9, sizeof(l_float32))) == NULL)
        return (l_float32 *)ERROR_PTR("mat not made", procName, NULL);

    mat[0] = scalex;
    mat[4] = scaley;
    mat[8] = 1;
    return mat;
}
