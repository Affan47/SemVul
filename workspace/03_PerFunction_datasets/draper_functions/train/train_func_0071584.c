f64vector_mul(const char *name,
                                 ScmObj d, ScmObj s0, ScmObj s1, int clamp)
{
    int i, size = SCM_F64VECTOR_SIZE(d), oor;
    double r, v0, v1;
    ScmObj rr, vv1;

    switch (arg2_check(name, s0, s1, TRUE)) {
    case ARGTYPE_UVECTOR:
        for (i=0; i<size; i++) {
            v0 = SCM_F64VECTOR_ELEMENTS(s0)[i];
            v1 = SCM_F64VECTOR_ELEMENTS(s1)[i];
            r = f64f64_mul(v0, v1, clamp);
            SCM_F64VECTOR_ELEMENTS(d)[i] = r;
        }
        break;
    case ARGTYPE_VECTOR:
        for (i=0; i<size; i++) {
            v0 = SCM_F64VECTOR_ELEMENTS(s0)[i];
            vv1 = SCM_VECTOR_ELEMENTS(s1)[i];
            v1 = f64num(vv1, &oor);
            if (!oor) {
                r = f64g_mul(v0, v1, clamp);
            } else {
                rr = Scm_MakeFlonum(v0);
                rr = Scm_Mul(rr, vv1);
                r = Scm_GetDouble(rr);
            }
            SCM_F64VECTOR_ELEMENTS(d)[i] = r;
        }
        break;
    case ARGTYPE_LIST:
        for (i=0; i<size; i++) {
            v0 = SCM_F64VECTOR_ELEMENTS(s0)[i];
            vv1 = SCM_CAR(s1); s1 = SCM_CDR(s1);
            v1 = f64num(vv1, &oor);
            if (!oor) {
                r = f64g_mul(v0, v1, clamp);
            } else {
                rr = Scm_MakeFlonum(v0);
                rr = Scm_Mul(rr, vv1);
                r = Scm_GetDouble(rr);
            }
            SCM_F64VECTOR_ELEMENTS(d)[i] = r;
        }
        break;
    case ARGTYPE_CONST:
        v1 = f64num(s1, &oor);
        for (i=0; i<size; i++) {
            v0 = SCM_F64VECTOR_ELEMENTS(s0)[i];
            if (!oor) {
                r = f64g_mul(v0, v1, clamp);
            } else {
                rr = Scm_MakeFlonum(v0);
                rr = Scm_Mul(rr, s1);
                r = Scm_GetDouble(rr);
            }
            SCM_F64VECTOR_ELEMENTS(d)[i] = r;
        }
    }
}
