fmorphautogen(SELA        *sela,
              l_int32      fileindex,
              const char  *filename)
{
l_int32  ret1, ret2;

    PROCNAME("fmorphautogen");

    if (!sela)
        return ERROR_INT("sela not defined", procName, 1);
    ret1 = fmorphautogen1(sela, fileindex, filename);
    ret2 = fmorphautogen2(sela, fileindex, filename);
    if (ret1 || ret2)
        return ERROR_INT("code generation problem", procName, 1);
    return 0;
}
