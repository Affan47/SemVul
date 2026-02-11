segment_create(opal_shmem_ds_t *ds_buf,
               const char *file_name,
               size_t size)
{
    int rc = OPAL_SUCCESS;
    pid_t my_pid = getpid();


    size_t real_size = size + sizeof(opal_shmem_seg_hdr_t);
    opal_shmem_seg_hdr_t *seg_hdrp = MAP_FAILED;


    shmem_ds_reset(ds_buf);


    if (-1 == (ds_buf->seg_id = shmem_posix_shm_open(
                                    ds_buf->seg_name,
                                    OPAL_SHMEM_POSIX_FILE_LEN_MAX - 1))) {


        rc = OPAL_ERROR;
        goto out;
    }

    else if (0 != ftruncate(ds_buf->seg_id, real_size)) {
        int err = errno;
        char hn[MAXHOSTNAMELEN];
        gethostname(hn, MAXHOSTNAMELEN - 1);
        hn[MAXHOSTNAMELEN - 1] = '\0';
        opal_show_help("help-opal-shmem-posix.txt", "sys call fail", 1, hn,
                       "ftruncate(2)", "", strerror(err), err);
        rc = OPAL_ERROR;
        goto out;
    }
    else if (MAP_FAILED == (seg_hdrp = (opal_shmem_seg_hdr_t*)mmap(NULL, real_size,
                                                                   PROT_READ | PROT_WRITE, MAP_SHARED,
                                                                   ds_buf->seg_id, 0))) {
        int err = errno;
        char hn[MAXHOSTNAMELEN];
        gethostname(hn, MAXHOSTNAMELEN - 1);
        hn[MAXHOSTNAMELEN - 1] = '\0';
        opal_show_help("help-opal-shmem-posix.txt", "sys call fail", 1, hn,
                       "mmap(2)", "", strerror(err), err);
        rc = OPAL_ERROR;
        goto out;
    }

    else {

        opal_atomic_rmb();


        opal_atomic_init(&seg_hdrp->lock, OPAL_ATOMIC_UNLOCKED);

        seg_hdrp->cpid = my_pid;

        opal_atomic_wmb();


        ds_buf->seg_cpid = my_pid;
        ds_buf->seg_size = real_size;
        ds_buf->seg_base_addr = (unsigned char *)seg_hdrp;


        OPAL_SHMEM_DS_SET_VALID(ds_buf);

        OPAL_OUTPUT_VERBOSE(
            (70, opal_shmem_base_framework.framework_output,
             "%s: %s: create successful "
             "(id: %d, size: %lu, name: %s)\n",
             mca_shmem_posix_component.super.base_version.mca_type_name,
             mca_shmem_posix_component.super.base_version.mca_component_name,
             ds_buf->seg_id, (unsigned long)ds_buf->seg_size, ds_buf->seg_name)
        );
    }

out:


    if (-1 != ds_buf->seg_id) {
        if (0 != close(ds_buf->seg_id)) {
            int err = errno;
            char hn[MAXHOSTNAMELEN];
            gethostname(hn, MAXHOSTNAMELEN - 1);
            hn[MAXHOSTNAMELEN - 1] = '\0';
            opal_show_help("help-opal-shmem-mmap.txt", "sys call fail", 1, hn,
                           "close(2)", "", strerror(err), err);
            rc = OPAL_ERROR;
         }
     }


    if (OPAL_SUCCESS != rc) {


        if (-1 != ds_buf->seg_id) {
            shm_unlink(ds_buf->seg_name);
        }
        if (MAP_FAILED != seg_hdrp) {
            munmap((void*)seg_hdrp, real_size);
        }

        shmem_ds_reset(ds_buf);
    }
    return rc;
}
