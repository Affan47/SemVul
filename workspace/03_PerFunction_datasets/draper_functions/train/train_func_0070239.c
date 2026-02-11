close_netcdf(void)
{
#ifdef ENABLE_C
    if (c_flag) cl_c(); else
#endif
#ifdef ENABLE_F77
    if (f77_flag) cl_f77(); else
#endif
#ifdef ENABLE_JAVA
    if (java_flag) cl_java(); else
#endif
#ifdef ENABLE_BINARY
    if (binary_flag) cl_netcdf();
#endif
}
