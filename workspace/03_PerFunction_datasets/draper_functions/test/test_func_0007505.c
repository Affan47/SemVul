boxSeparationDistance(BOX      *box1,
                      BOX      *box2,
                      l_int32  *ph_sep,
                      l_int32  *pv_sep)
{
l_int32  l1, t1, w1, h1, r1, b1, l2, t2, w2, h2, r2, b2;

    PROCNAME("boxSeparationDistance");

    if (!ph_sep && !pv_sep)
        return ERROR_INT("nothing to do", procName, 1);
    if (ph_sep) *ph_sep = 0;
    if (pv_sep) *pv_sep = 0;
    if (!box1 || !box2)
        return ERROR_INT("box1 and box2 not both defined", procName, 1);

    if (ph_sep) {
        boxGetGeometry(box1, &l1, NULL, &w1, NULL);
        boxGetGeometry(box2, &l2, NULL, &w2, NULL);
        r1 = l1 + w1;
        r2 = l2 + w2;
        if (l2 >= l1)
            *ph_sep = l2 - r1;
        else
            *ph_sep = l1 - r2;
    }
    if (pv_sep) {
        boxGetGeometry(box1, NULL, &t1, NULL, &h1);
        boxGetGeometry(box2, NULL, &t2, NULL, &h2);
        b1 = t1 + h1;
        b2 = t2 + h2;
        if (t2 >= t1)
            *pv_sep = t2 - b1;
        else
            *pv_sep = t1 - b2;
    }
    return 0;
}
