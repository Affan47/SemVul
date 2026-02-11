vec_array_print(ScmObj obj, ScmPort *out, ScmWriteContext *ctx)
{
    ScmVector4fArray *va = SCM_VECTOR4F_ARRAY(obj);
    int len = SCM_VECTOR4F_ARRAY_SIZE(va), i;
    Scm_Printf(out, "#,(vector4f-array %d ", len);
    for (i = 0; i < len; i++) {
        float *z = Scm_Vector4fArrayRefv(va, i);
        Scm_Printf(out, "(%g %g %g %g) ", z[0], z[1], z[2], z[3]);
    }
    Scm_Printf(out, ")");
}
