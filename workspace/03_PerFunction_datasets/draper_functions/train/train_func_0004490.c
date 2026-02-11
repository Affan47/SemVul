Scm_ObjArrayToF64Vector(ScmObj *arr, int size, int clamp)
{
    int i;
    ScmUVector *vec = (ScmUVector*)Scm_MakeF64Vector(size, 0);
    for (i=0; i<size; i++) {
        double elt;
        ScmObj obj = arr[i];
        elt = Scm_GetDouble(obj);
        SCM_F64VECTOR_ELEMENTS(vec)[i] = elt;
    }
    return SCM_OBJ(vec);
}
