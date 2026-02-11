clamp_poles(double *T0, double *T1, int ii, int i, double * pole,
                int p_offset, int pole_step, int pole_step_i, int order)
{
    if (ii < 0) {
        if (order == 3)
            subcurve(pole + p_offset, pole_step_i, T0[i], T1[i]);
        else
            subline(pole + p_offset, pole_step_i, T0[i], T1[i]);
    } else if (i == ii) {
        clamp_poles(T0, T1, ii - 1, i, pole, p_offset, pole_step / 4, pole_step, order);
    } else {
        int j, ei = (T0[ii] == T1[ii] ? 1 : order + 1);

        for (j = 0; j < ei; j++)
            clamp_poles(T0, T1, ii - 1, i, pole, p_offset + j * pole_step,
                            pole_step / 4, pole_step_i, order);
    }
}
