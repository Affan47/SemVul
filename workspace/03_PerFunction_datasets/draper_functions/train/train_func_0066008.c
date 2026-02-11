boinc_graphics_make_shmem(const char* prog_name, int size) {
#ifdef _WIN32
    HANDLE shmem_handle;
    char shmem_name[MAXPATHLEN];
    void* p;
    get_shmem_name(prog_name, shmem_name);
    shmem_handle = create_shmem(shmem_name, size, &p);
    if (shmem_handle == NULL) return 0;
    return p;
#else
    void* p;
#ifdef __EMX__
    key_t key = get_shmem_name(prog_name);
    int retval = create_shmem(key, size, 0, &p);
#else

    char shmem_name[MAXPATHLEN];
    get_shmem_name(prog_name, shmem_name);
    int retval = create_shmem_mmap(shmem_name, size, &p);


    if (retval == 0) chmod(shmem_name, 0666);
#endif
    if (retval) return 0;
    return p;
#endif
}
