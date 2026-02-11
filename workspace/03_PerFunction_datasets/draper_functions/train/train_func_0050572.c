vec_lmsf(const float x[], float y[], int n, float error)
{
    int i;
    __m128 n1;
    __m128 n2;
    __m128 n3;
    __m128 n4;

    if ((i = n & ~3))
    {
        n3 = _mm_set1_ps(error);
        n4 = _mm_set1_ps(LMS_LEAK_RATE);
        for (i -= 4;  i >= 0;  i -= 4)
        {
            n1 = _mm_loadu_ps(x + i);
            n2 = _mm_loadu_ps(y + i);
            n1 = _mm_mul_ps(n1, n3);
            n2 = _mm_mul_ps(n2, n4);
            n1 = _mm_add_ps(n1, n2);
            _mm_storeu_ps(y + i, n1);
        }
    }

    switch (n & 3)
    {
    case 3:
        y[n - 3] = y[n - 3]*LMS_LEAK_RATE + x[n - 3]*error;
    case 2:
        y[n - 2] = y[n - 2]*LMS_LEAK_RATE + x[n - 2]*error;
    case 1:
        y[n - 1] = y[n - 1]*LMS_LEAK_RATE + x[n - 1]*error;
    }
}
