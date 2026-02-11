Scm_AxesToQuatfv(float r[],
                      const float v1[],
                      const float v2[],
                      const float w1[],
                      const float w2[])
{
    float q1[4], q2[4], c, t, s2, axis[4], wt[4];
    Scm_VectorsToQuatfv(q1, v1, w1);
    Scm_QuatfTransformv(wt, q1, v2);
    SCM_VECTOR4F_CROSSV(axis, wt, w2);
    SCM_VECTOR4F_NORMALIZEV(axis);
    c = SCM_VECTOR4F_DOTV(w2, wt);
    if (c < -1.0f) c = -1.0f;
    else if (c > 1.0f)  c = 1.0f;
    t = acosf(c);
    s2 = sinf(t/2);
    q2[0] = axis[0] * s2; q2[1] = axis[1] * s2; q2[2] = axis[2] * s2;
    q2[3] = cosf(t/2);
    Scm_QuatfMulv(r, q2, q1);
}
