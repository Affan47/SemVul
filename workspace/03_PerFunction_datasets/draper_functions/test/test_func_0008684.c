rand_gen_set_init(RandGenSet *rngset,
                  guint seed)
{
    guint i;

    for (i = 0; i < rngset->n; i++)
        g_rand_set_seed(rngset->rng[i], seed + i);
}
