filter_periodic(coeff_t *input_signal, coeff_t *output_signal,
                                  int signal_length, filter_t *filter)
{
    int i, j, k;

    switch (filter->causality) {
        case CAUSAL:
        {
            for (i = 0; i < signal_length; i += 1) {
                output_signal[i] = 0;
                for (j = 0; j < filter->length; j++) {
                    k = periodic_extension(i - j, signal_length);
                    output_signal[i] += input_signal[k] * filter->coeffs[j];
                }
            }

            break;
        }
        case ANTICAUSAL:
        {
            for (i = 0; i < signal_length; i += 2) {
                output_signal[i] = 0;
                for (j = 0; j < filter->length; j++) {
                    k = periodic_extension(i + j, signal_length);
                    output_signal[i] +=
                        input_signal[k] * filter->coeffs[filter->length - j - 1];
                }
            }

            break;
        }
        default:
        {
            assert(0);
            break;
        }
    }
}
