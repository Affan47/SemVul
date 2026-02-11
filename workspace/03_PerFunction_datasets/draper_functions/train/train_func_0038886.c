gf2x_tfft_dft_inner(gf2x_tfft_info_srcptr o, gf2x_tfft_ptr tr, const unsigned long * a, size_t bits_a, size_t M)
{
    size_t K = o->K;
    size_t Mp = CEIL(M, K / 3);
    size_t Np = Mp * (K / 3);
    size_t np = W(Np);


    unsigned long ** A = malloc_or_die(K * sizeof(unsigned long *));
    for (size_t i = 0; i < K; i++) A[i] = tr + 2 * i * np;
    decompose(A, a, W(bits_a), M, K, np);
    unsigned long * tmp1, * tmp2, * tmp3;
    tmp1 = o->tmp;
    tmp2 = o->tmp + 2 * np;
    tmp3 = o->tmp + 4 * np;
    fft(A, K, Mp, Np, 1, tmp1, tmp2, tmp3, o->perm);
    free(A);
}
