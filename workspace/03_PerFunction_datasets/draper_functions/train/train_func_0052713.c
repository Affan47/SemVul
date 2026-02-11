jack_attach_lib_shm_read (jack_shm_info_t* si)
{
    int res = jack_attach_shm_read(si);
    if (res == 0)
        si->size = jack_shm_registry[si->index].size;
    return res;
}
