Scm_ObjArrayToS64Vector(ScmObj *arr, int size, int clamp)
{
    int i;
    ScmUVector *vec = (ScmUVector*)Scm_MakeS64Vector(size, 0);
    for (i=0; i<size; i++) {
        ScmInt64 elt;
        ScmObj obj = arr[i];
        elt = Scm_GetInteger64Clamp(obj, clamp, NULL);
        SCM_S64VECTOR_ELEMENTS(vec)[i] = elt;
    }
    return SCM_OBJ(vec);
}
