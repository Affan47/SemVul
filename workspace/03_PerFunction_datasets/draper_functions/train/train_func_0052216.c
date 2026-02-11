AddNode(RxNode **F, RxNode **N, RxNode *A) {
    if (A) {
        if (*F) {
            (*N)->fNext = A;
            A->fPrev = (*N);
            *N = A;
        } else {
            (*N) = (*F) = A;
            A->fPrev = A->fNext = 0;
        }
        return 1;
    }
    return 0;
}
