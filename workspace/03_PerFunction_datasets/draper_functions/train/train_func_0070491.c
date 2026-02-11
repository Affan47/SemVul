pivot(DenseMatrix &B, unsigned r, unsigned c)
{
    unsigned k = r;

    if (eq(B.m_[r*B.col_ + c], zero))
        for (k = r; k < B.row_; k++)
            if (!eq(B.m_[k*B.col_ + c], zero))
                break;
    return k;
}
