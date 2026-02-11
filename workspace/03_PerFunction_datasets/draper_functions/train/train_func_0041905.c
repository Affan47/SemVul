Scm_MinMax(ScmObj arg0, ScmObj args, ScmObj *min, ScmObj *max)
{
    int inexact = !SCM_EXACTP(arg0);
    ScmObj mi = arg0;
    ScmObj ma = arg0;

    for (;;) {
        if (!SCM_REALP(arg0))
            Scm_Error("real number required, but got %S", arg0);
        if (SCM_NULLP(args)) {
            if (min) {
                if (inexact && SCM_EXACTP(mi)) {
                    *min = Scm_Inexact(mi);
                } else {
                    *min = mi;
                }
            }
            if (max) {
                if (inexact && SCM_EXACTP(ma)) {
                    *max = Scm_Inexact(ma);
                } else {
                    *max = ma;
                }
            }
            return;
        }
        if (!SCM_EXACTP(SCM_CAR(args))) inexact = TRUE;
        if (min && Scm_NumCmp(mi, SCM_CAR(args)) > 0) {
            mi = SCM_CAR(args);
        }
        if (max && Scm_NumCmp(ma, SCM_CAR(args)) < 0) {
            ma = SCM_CAR(args);
        }
        args = SCM_CDR(args);
    }
}
