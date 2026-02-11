nlSparseMatrixNNZ( NLSparseMatrix* M) {
    NLuint nnz = 0 ;
    NLuint i ;
    if(M->storage & NL_MATRIX_STORE_ROWS) {
        for(i = 0; i<M->m; i++) {
            nnz += M->row[i].size ;
        }
    } else if (M->storage & NL_MATRIX_STORE_COLUMNS) {
        for(i = 0; i<M->n; i++) {
            nnz += M->column[i].size ;
        }
    } else {
        nl_assert_not_reached ;
    }
    return nnz ;
}
