invert(int32_t order, float phi[], float psi[], float rc[])
{
    float r1;
    int32_t i;
    int32_t j;
    int32_t k;
    float v[10][10];

    for (j = 0;  j < order;  j++)
    {
        for (i = j;  i < order;  i++)
            v[j][i] = phi[i + j*order];
        for (k = 0;  k < j;  k++)
        {
            r1 = v[k][j]*v[k][k];
            for (i = j;  i <= order;  i++)
                v[j][i] -= v[k][i]*r1;
        }

        if (fabsf(v[j][j]) < 1.0e-10f)
        {
            for (i = j;  i < order;  i++)
                rc[i] = 0.0f;
            return;
        }
        rc[j] = psi[j];
        for (k = 0;  k < j;  k++)
            rc[j] -= rc[k]*v[k][j];
        v[j][j] = 1.0f/v[j][j];
        rc[j] *= v[j][j];
        r1 = min(rc[j], 0.999f);
        rc[j] = max(r1, -0.999f);
    }
}
