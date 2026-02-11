from_coo(unsigned row, unsigned col,
    const std::vector<unsigned>& i, const std::vector<unsigned>& j,
    const vec_basic& x)
{
    unsigned nnz = x.size();
    std::vector<unsigned> p_ = std::vector<unsigned>(row + 1, 0);
    std::vector<unsigned> j_ = std::vector<unsigned>(nnz);
    vec_basic x_ = vec_basic(nnz);

    for (unsigned n = 0; n < nnz; n++) {
        p_[i[n]]++;
    }


    unsigned temp;
    for (unsigned i = 0, cumsum = 0; i < row; i++) {
        temp = p_[i];
        p_[i] = cumsum;
        cumsum += temp;
    }
    p_[row] = nnz;


    unsigned row_, dest_;
    for (unsigned n = 0; n < nnz; n++) {
        row_  = i[n];
        dest_ = p_[row_];

        j_[dest_] = j[n];
        x_[dest_] = x[n];

        p_[row_]++;
    }

    for (unsigned i = 0, last = 0; i <= row; i++) {
        std::swap(p_[i], last);
    }


    csr_sort_indices(p_, j_, x_, row);

    csr_sum_duplicates(p_, j_, x_, row);

    CSRMatrix B = CSRMatrix(row, col, std::move(p_), std::move(j_), std::move(x_));
    return B;
}
