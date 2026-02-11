r_REFINE_LP(struct rbitstream*str, int coeff, int model_bits)
{
    int coeff_refinement = _jxr_rbitstream_uintN(str, model_bits);

    if (coeff > 0) {
        coeff <<= model_bits;
        coeff += coeff_refinement;
    } else if (coeff < 0) {
        coeff <<= model_bits;
        coeff -= coeff_refinement;
    } else {
        coeff = coeff_refinement;
        if (coeff) {
            int sign_flag = _jxr_rbitstream_uint1(str);
            if (sign_flag)
                coeff = -coeff;
        }
    }

    return coeff;
}
