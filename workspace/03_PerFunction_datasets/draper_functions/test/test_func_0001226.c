fortuna_seed(const void *indata, int size)
{
    HEIMDAL_MUTEX_lock(&fortuna_mutex);

    fortuna_init();
    add_entropy(&main_state, indata, size);
    if (size >= INIT_BYTES)
	have_entropy = 1;

    HEIMDAL_MUTEX_unlock(&fortuna_mutex);
}
