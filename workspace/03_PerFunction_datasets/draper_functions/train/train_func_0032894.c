numaMakeThresholdIndicator(NUMA      *nas,
                           l_float32  thresh,
                           l_int32    type)
{
l_int32    n, i, ival;
l_float32  fval;
NUMA      *nai;

    PROCNAME("numaMakeThresholdIndicator");

    n = numaGetCount(nas);
    nai = numaCreate(n);
    for (i = 0; i < n; i++) {
        numaGetFValue(nas, i, &fval);
        ival = 0;
        switch (type)
        {
        case L_SELECT_IF_LT:
            if (fval < thresh) ival = 1;
            break;
        case L_SELECT_IF_GT:
            if (fval > thresh) ival = 1;
            break;
        case L_SELECT_IF_LTE:
            if (fval <= thresh) ival = 1;
            break;
        case L_SELECT_IF_GTE:
            if (fval >= thresh) ival = 1;
            break;
        default:
            numaDestroy(&nai);
            return (NUMA *)ERROR_PTR("invalid type", procName, NULL);
        }
        numaAddNumber(nai, ival);
    }

    return nai;
}
