init_s3_values(FLOAT ** p,
               int (*s3ind)[2], int npart, FLOAT const *bval, FLOAT const *bval_width,
               FLOAT const *norm, int use_old_s3)
{
    FLOAT   s3[CBANDS][CBANDS];


    int     i, j, k;
    int     numberOfNoneZero = 0;


    if (use_old_s3) {
        for (i = 0; i < npart; i++) {
            for (j = 0; j < npart; j++) {
                FLOAT   v = s3_func(bval[i] - bval[j]) * bval_width[j];
                s3[i][j] = v * norm[i];
            }
        }
    }
    else {
        for (j = 0; j < npart; j++) {
            FLOAT   hf_slope = 15 + Min(21 / bval[j], 12);
            FLOAT   s3_x_norm = norm_s3_func_x(hf_slope);
            for (i = 0; i < npart; i++) {
                FLOAT   v = s3_x_norm * s3_func_x(bval[i] - bval[j], hf_slope) * bval_width[j];
                s3[i][j] = v * norm[i];
            }
        }
    }
    for (i = 0; i < npart; i++) {
        for (j = 0; j < npart; j++) {
            if (s3[i][j] > 0.0f)
                break;
        }
        s3ind[i][0] = j;

        for (j = npart - 1; j > 0; j--) {
            if (s3[i][j] > 0.0f)
                break;
        }
        s3ind[i][1] = j;
        numberOfNoneZero += (s3ind[i][1] - s3ind[i][0] + 1);
    }
    *p = malloc(sizeof(FLOAT) * numberOfNoneZero);
    if (!*p)
        return -1;

    k = 0;
    for (i = 0; i < npart; i++)
        for (j = s3ind[i][0]; j <= s3ind[i][1]; j++)
            (*p)[k++] = s3[i][j];

    return 0;
}
