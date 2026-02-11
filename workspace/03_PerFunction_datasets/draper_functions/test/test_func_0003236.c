convertRGBToHSV(l_int32   rval,
                l_int32   gval,
                l_int32   bval,
                l_int32  *phval,
                l_int32  *psval,
                l_int32  *pvval)
{
l_int32    minrg, maxrg, min, max, delta;
l_float32  h;

    PROCNAME("convertRGBToHSV");

    if (!phval || !psval || !pvval)
        return ERROR_INT("&hval, &sval, &vval not all defined", procName, 1);

    minrg = L_MIN(rval, gval);
    min = L_MIN(minrg, bval);
    maxrg = L_MAX(rval, gval);
    max = L_MAX(maxrg, bval);
    delta = max - min;

    *pvval = max;
    if (delta == 0) {
        *phval = 0;
        *psval = 0;
    }
    else {
        *psval = (l_int32)(255. * (l_float32)delta / (l_float32)max + 0.5);
        if (rval == max)
            h = (l_float32)(gval - bval) / (l_float32)delta;
        else if (gval == max)
            h = 2. + (l_float32)(bval - rval) / (l_float32)delta;
        else
            h = 4. + (l_float32)(rval - gval) / (l_float32)delta;
        h *= 40.0;
        if (h < 0.0)
          h += 240.0;
        *phval = (l_int32)(h + 0.5);
    }

    return 0;
}
