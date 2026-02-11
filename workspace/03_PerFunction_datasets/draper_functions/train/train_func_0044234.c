plfit_walker_alias_sampler_sample(const plfit_walker_alias_sampler_t* sampler,
        long int *xs, size_t n, mt_rng_t* rng) {
    double u;
    long int j;
    long int *x;

    x = xs;

    if (rng == 0) {

        while (n > 0) {
            u = rand() / ((double)RAND_MAX);
            j = rand() % sampler->num_bins;
            *x = (u < sampler->probs[j]) ? j : sampler->indexes[j];
            n--; x++;
        }
    } else {

        while (n > 0) {
            u = mt_uniform_01(rng);
            j = mt_random(rng) % sampler->num_bins;
            *x = (u < sampler->probs[j]) ? j : sampler->indexes[j];
            n--; x++;
        }
    }

    return PLFIT_SUCCESS;
}
