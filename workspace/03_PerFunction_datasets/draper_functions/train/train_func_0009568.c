regular_multiply(BI_CTX *ctx, bigint *bia, bigint *bib)
{
    int i, j, i_plus_j;
    int n = bia->size;
    int t = bib->size;
    bigint *biR = alloc(ctx, n + t);
    comp *sr = biR->comps;
    comp *sa = bia->comps;
    comp *sb = bib->comps;

    check(bia);
    check(bib);


    memset(biR->comps, 0, ((n+t)*COMP_BYTE_SIZE));
    i = 0;

    do
    {
        comp carry = 0;
        comp b = *sb++;
        i_plus_j = i;
        j = 0;

        do
        {
            long_comp tmp = sr[i_plus_j] + (long_comp)sa[j]*b + carry;
            sr[i_plus_j++] = (comp)tmp;
            carry = (comp)(tmp >> COMP_BIT_SIZE);
        } while (++j < n);

        sr[i_plus_j] = carry;
    } while (++i < t);

    bi_free(ctx, bia);
    bi_free(ctx, bib);
    return trim(biR);
}
