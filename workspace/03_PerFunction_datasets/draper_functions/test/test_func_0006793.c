circumCircle(const float* p1, const float* p2, const float* p3,
                         float* c, float& r)
{
    static const float EPS = 1e-6f;

    const float cp = vcross2(p1, p2, p3);
    if (fabsf(cp) > EPS)
    {
        const float p1Sq = vdot2(p1,p1);
        const float p2Sq = vdot2(p2,p2);
        const float p3Sq = vdot2(p3,p3);
        c[0] = (p1Sq*(p2[2]-p3[2]) + p2Sq*(p3[2]-p1[2]) + p3Sq*(p1[2]-p2[2])) / (2*cp);
        c[2] = (p1Sq*(p3[0]-p2[0]) + p2Sq*(p1[0]-p3[0]) + p3Sq*(p2[0]-p1[0])) / (2*cp);
        r = vdist2(c, p1);
        return true;
    }

    c[0] = p1[0];
    c[2] = p1[2];
    r = 0;
    return false;
}
