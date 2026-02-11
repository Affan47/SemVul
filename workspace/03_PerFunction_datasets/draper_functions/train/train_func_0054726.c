pivoted_gauss_jordan_elimination(const DenseMatrix &A, DenseMatrix &B,
    std::vector<unsigned> &pivotlist)
{
    CSYMPY_ASSERT(A.row_ == B.row_ && A.col_ == B.col_);
    CSYMPY_ASSERT(pivotlist.size() == A.row_);

    unsigned row = A.row_, col = A.col_;
    unsigned index = 0, i, j, k;
    RCP<const Basic> scale;
    B.m_ = A.m_;

    for (i = 0; i < row; i++)
        pivotlist[i] = i;

    for (i = 0; i < col; i++) {
        if (index == row)
            break;

        k = pivot(B, index, i);
        if (k == row)
            continue;
        if (k != index) {
            row_exchange_dense(B, k, index);
            std::swap(pivotlist[k], pivotlist[index]);
        }

        scale = div(one, B.m_[index*col + i]);
        row_mul_scalar_dense(B, index, scale);

        for (j = 0; j < row; j++) {
            if (j == index)
                continue;

            scale = mul(minus_one, B.m_[j*col + i]);
            row_add_row_dense(B, j, index, scale);
        }

        index++;
    }
}
