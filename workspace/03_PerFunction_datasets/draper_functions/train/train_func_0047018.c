eekf_mat_chol(eekf_mat *L, eekf_mat const *A)
{
    if (NULL == L || NULL == A || A->rows * A->cols != L->rows * L->cols
            || A->rows != A->cols)
    {
        return NULL;
    }

    uint16_t n, N, r, c;
    uint16_t offset;
    eekf_value *de, *value;

    N = A->cols;

    L->rows = N;
    L->cols = N;

    memset(L->elements, 0, sizeof(eekf_value) * N * N);
    for (n = 0; n < N; n++)
    {
        offset = n * N + n;
        memcpy(L->elements + offset, A->elements + offset,
                sizeof(eekf_value) * (N - n));
    }


    for (n = 0; n < N; n++)
    {

        de = L->elements + n * N + n;

        if (*de <= 0)
        {
            return NULL;
        }

        *de = EEKF_MAT_SQRT(*de);

        for (r = 1; r < N - n; r++)
        {
            *(de + r) /= *de;
        }

        for (c = n + 1; c < N; c++)
        {
            value = L->elements + c * N + c;
            for (r = c; r < N; r++, value++)
            {
                *value -= *(L->elements + n * N + r)
                        * *(L->elements + n * N + c);
            }
        }
    }

    return L;
}
