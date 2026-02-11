gs_matrix_fixed_from_matrix(gs_matrix_fixed *pfmat, const gs_matrix *pmat)
{
    *(gs_matrix *)pfmat = *pmat;
    if (f_fits_in_fixed(pmat->tx) && f_fits_in_fixed(pmat->ty)) {
        pfmat->tx = fixed2float(pfmat->tx_fixed = float2fixed(pmat->tx));
        pfmat->ty = fixed2float(pfmat->ty_fixed = float2fixed(pmat->ty));
        pfmat->txy_fixed_valid = true;
    } else {
        pfmat->txy_fixed_valid = false;
    }
    return 0;
}
