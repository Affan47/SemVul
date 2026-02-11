predictor_init_state(int *k, int *state, int order)
{
    int i;

    for (i = order-2; i >= 0; i--)
    {
        int j, p, x = state[i];

        for (j = 0, p = i+1; p < order; j++,p++)
            {
            int tmp = x + shift_down(k[j] * state[p], LATTICE_SHIFT);
            state[p] += shift_down(k[j]*x, LATTICE_SHIFT);
            x = tmp;
        }
    }
}
