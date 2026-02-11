ntru_from_sves(uint8_t *M, uint16_t M_len, uint16_t N, uint16_t skip, NtruIntPoly *poly) {
    poly->N = N;

    uint16_t coeff_idx = skip ? 1 : 0;
    uint16_t i = 0;
    while (i<M_len/3*3 && coeff_idx<N-1) {

        int32_t chunk = (uint8_t)M[i+2];
        chunk <<= 8;
        chunk += (uint8_t)M[i+1];
        chunk <<= 8;
        chunk += (uint8_t)M[i];
        i += 3;

        uint8_t j;
        for (j=0; j<8 && coeff_idx<N-1; j++) {

            uint8_t coeff_tbl_idx = ((chunk&1)<<2) + (chunk&2) + ((chunk&4)>>2);
            poly->coeffs[coeff_idx++] = NTRU_COEFF1_TABLE[coeff_tbl_idx];
            poly->coeffs[coeff_idx++] = NTRU_COEFF2_TABLE[coeff_tbl_idx];
            chunk >>= 3;
        }
    }

    while (coeff_idx < N)
        poly->coeffs[coeff_idx++] = 0;
}
