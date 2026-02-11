gf2x_tfft_compose_inner(gf2x_tfft_info_srcptr o, gf2x_tfft_ptr tc, gf2x_tfft_srcptr ta, gf2x_tfft_srcptr tb, size_t M)
{
    size_t K = o->K;

    size_t Np = compute_Np(M, K);
    size_t np = W(Np);
    unsigned long * tmp1 = o->tmp;


    unsigned long * tmp3 = o->tmp + 4 * np;

    for (size_t i = 0; i < K; i++) {
	MulMod(tc, ta, tb, Np, tmp1, tmp3);
        ta += 2 * np;
        tb += 2 * np;
        tc += 2 * np;
    }
}
