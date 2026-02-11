get_uniq_file_name(const char *base_path, const char *hash_key)
{
    char *uniq_name_buf = NULL;
    unsigned long str_hash = 0;
    pid_t my_pid;
    opal_rng_buff_t rand_buff;
    uint32_t rand_num;


    if (NULL == hash_key) {
        return NULL;
    }
    if (NULL == (uniq_name_buf = calloc(OPAL_PATH_MAX, sizeof(char)))) {

        return NULL;
    }

    my_pid = getpid();
    opal_srand(&rand_buff,((uint32_t)(time(NULL) + my_pid)));
    rand_num = opal_rand(&rand_buff) % 1024;
    str_hash = sdbm_hash((unsigned char *)hash_key);

    snprintf(uniq_name_buf, OPAL_PATH_MAX, "%s/open_mpi_shmem_mmap.%d_%lu_%d",
             base_path, (int)my_pid, str_hash, rand_num);

    return uniq_name_buf;
}
