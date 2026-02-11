eekf_mat_fw_sub(eekf_mat *X, eekf_mat const *L, eekf_mat const *B)
{
    if (NULL == X || NULL == L || NULL == B || L->rows != B->rows
            || X->rows * X->cols != B->cols * L->cols)
    {
        return NULL;
    }


    X->rows = L->cols;
    X->cols = B->cols;


    uint8_t i, j, k;
    eekf_value *b_i, *x_i, *x_j, *diag, *row, *a_ij;


    for (k = 0; k < X->cols; k++)
    {

        for (i = 0, x_i = EEKF_MAT_COL(*X, k), b_i = EEKF_MAT_COL(*B, k), diag =
                L->elements, row = L->elements; i < X->rows;
                i++, diag += L->rows + 1, x_i++, b_i++, row++)
        {
            *x_i = *b_i;

            for (j = 0, x_j = EEKF_MAT_COL(*X, k), a_ij = row; j < i;
                    j++, x_j++, a_ij += L->rows)
            {
                *x_i -= *a_ij * *x_j;
            }

            *x_i /= *diag;
        }
    }

    return X;
}
