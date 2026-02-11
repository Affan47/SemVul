garray_getfloatarray(t_garray *x, int *size, t_float **vec)
{
    if (sizeof(t_word) != sizeof(t_float))
    {
        static int warned;
        if (!warned)
            post(
 "warning: extern using garray_getfloatarray() won't work in 64-bit version");
        warned = 1;
    }
    return (garray_getfloatwords(x, size, (t_word **)vec));
}
