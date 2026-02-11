ntru_to_arr(NtruIntPoly *p, int q, char *a) {
    int bits_coeff = 0;
    while (q > 1) {
        q /= 2;
        bits_coeff++;
    }

    int bit_idx = 0;
    int byte_idx = 0;
    int i, j;
    a[0] = 0;
    for (i=0; i<p->N; i++)
        for (j=0; j<bits_coeff; j++) {
            int curr_bit = (p->coeffs[i] >> j) & 1;
            a[byte_idx] |= curr_bit << bit_idx;
            if (bit_idx == 7) {
                bit_idx = 0;
                byte_idx++;
                a[byte_idx] = 0;
            }
            else
                bit_idx++;
        }
}
