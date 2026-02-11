rand_start(rb_random_t *r)
{
    struct MT *mt = &r->mt;
    if (!genrand_initialized(mt)) {
	r->seed = rand_init(mt, random_seed());
    }
    return r;
}
