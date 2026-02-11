regTestCompareValues(L_REGPARAMS  *rp,
                     l_float32     val1,
                     l_float32     val2,
                     l_float32     delta)
{
l_float32  diff;

    PROCNAME("regTestCompareValues");

    if (!rp)
        return ERROR_INT("rp not defined", procName, 1);

    rp->index++;
    diff = L_ABS(val2 - val1);


    if (diff > delta) {
        if (rp->fp) {
            fprintf(rp->fp,
                    "Failure in %s_reg: value comparison for index %d\n"
                    "difference = %f but allowed delta = %f\n",
                    rp->testname, rp->index, diff, delta);
        }
        fprintf(stderr,
                    "Failure in %s_reg: value comparison for index %d\n"
                    "difference = %f but allowed delta = %f\n",
                    rp->testname, rp->index, diff, delta);
        rp->success = FALSE;
    }
    return 0;
}
