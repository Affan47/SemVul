dewarpaSetValidModels(L_DEWARPA  *dewa,
                      l_int32     notests,
                      l_int32     debug)
{
l_int32    i, n, maxcurv, diffcurv, diffedge;
L_DEWARP  *dew;

    PROCNAME("dewarpaSetValidModels");

    if (!dewa)
        return ERROR_INT("dewa not defined", procName, 1);

    n = dewa->maxpage + 1;
    for (i = 0; i < n; i++) {
        if ((dew = dewarpaGetDewarp(dewa, i)) == NULL)
            continue;

        if (debug) {
            if (dew->hasref == 1) {
                L_INFO("page %d: has only a ref model\n", procName, i);
            } else if (dew->vsuccess == 0) {
                L_INFO("page %d: no model successfully built\n",
                       procName, i);
            } else if (!notests) {
                maxcurv = L_MAX(L_ABS(dew->mincurv), L_ABS(dew->maxcurv));
                diffcurv = dew->maxcurv - dew->mincurv;
                if (dewa->useboth && !dew->hsuccess)
                    L_INFO("page %d: useboth, but no horiz disparity\n",
                               procName, i);
                if (maxcurv > dewa->max_linecurv)
                    L_INFO("page %d: max curvature %d > max_linecurv\n",
                                procName, i, diffcurv);
                if (diffcurv < dewa->min_diff_linecurv)
                    L_INFO("page %d: diff curv %d < min_diff_linecurv\n",
                                procName, i, diffcurv);
                if (diffcurv > dewa->max_diff_linecurv)
                    L_INFO("page %d: abs diff curv %d > max_diff_linecurv\n",
                                procName, i, diffcurv);
                if (dew->hsuccess) {
                    diffedge = L_ABS(dew->leftcurv - dew->rightcurv);
                    if (L_ABS(dew->leftcurv) > dewa->max_edgecurv)
                        L_INFO("page %d: left curvature %d > max_edgecurv\n",
                                    procName, i, dew->leftcurv);
                    if (L_ABS(dew->rightcurv) > dewa->max_edgecurv)
                        L_INFO("page %d: right curvature %d > max_edgecurv\n",
                               procName, i, dew->rightcurv);
                    if (diffedge > dewa->max_diff_edgecurv)
                        L_INFO("page %d: abs diff left-right curv %d > "
                               "max_diff_edgecurv\n", procName, i, diffedge);
                }
            }
        }

        dewarpaTestForValidModel(dewa, dew, notests);
    }

    return 0;
}
