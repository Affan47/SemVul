csr_matmat_pass1(const CSRMatrix &A, const CSRMatrix &B, CSRMatrix &C)
{

    std::vector<unsigned> mask(A.col_, -1);
    C.p_[0] = 0;

    unsigned nnz = 0;
    for (unsigned i = 0; i < A.row_; i++) {

        unsigned row_nnz = 0;

        for (unsigned jj = A.p_[i]; jj < A.p_[i + 1]; jj++) {
            unsigned j = A.j_[jj];
            for (unsigned kk = B.p_[j]; kk < B.p_[j + 1]; kk++) {
                unsigned k = B.j_[kk];
                if(mask[k] != i){
                    mask[k] = i;
                    row_nnz++;
                }
            }
        }

        unsigned next_nnz = nnz + row_nnz;


        if (next_nnz < nnz) {
            throw std::overflow_error("nnz of the result is too large");
        }

        nnz = next_nnz;
        C.p_[i + 1] = nnz;
    }
}
