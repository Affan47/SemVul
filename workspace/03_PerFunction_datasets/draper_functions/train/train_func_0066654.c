overlapSegSeg2d(const float* a, const float* b, const float* c, const float* d)
{
    const float a1 = vcross2(a, b, d);
    const float a2 = vcross2(a, b, c);
    if (a1*a2 < 0.0f)
    {
        float a3 = vcross2(c, d, a);
        float a4 = a3 + a2 - a1;
        if (a3 * a4 < 0.0f)
            return 1;
    }
    return 0;
}
