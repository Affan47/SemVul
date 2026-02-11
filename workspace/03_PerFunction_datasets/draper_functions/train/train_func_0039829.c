detect_C89_floats(void) HDF_NO_UBSAN
{
    DETECT_F(float,     FLOAT,      d_g[nd_g]); nd_g++;
    DETECT_F(double,    DOUBLE,     d_g[nd_g]); nd_g++;
}
