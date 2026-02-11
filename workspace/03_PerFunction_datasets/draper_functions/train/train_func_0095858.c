segment_create(opal_shmem_ds_t *ds_buf,
               const char *file_name,
               size_t size)
{
    int rc = OPAL_SUCCESS;
    pid_t my_pid = getpid();


    size_t real_size = size + sizeof(opal_shmem_seg_hdr_t);
    opal_shmem_seg_hdr_t *seg_hdrp = MAP_FAILED;


    shmem_ds_reset(ds_buf);


    if (-1 == (ds_buf->seg_id = shmget(IPC_PRIVATE, real_size,
                                       IPC_CREAT | IPC_EXCL | S_IRWXU))) {
        int err = errno;
        char hn[MAXHOSTNAMELEN];
        gethostname(hn, MAXHOSTNAMELEN - 1);
        hn[MAXHOSTNAMELEN - 1] = '\0';
        opal_show_help("help-opal-shmem-sysv.txt", "sys call fail", 1, hn,
                       "shmget(2)", "", strerror(err), err);
        rc = OPAL_ERROR;
        goto out;
    }

    else if ((void *)-1 == (seg_hdrp = shmat(ds_buf->seg_id, NULL, 0))) {
        int err = errno;
        char hn[MAXHOSTNAMELEN];
        gethostname(hn, MAXHOSTNAMELEN - 1);
        hn[MAXHOSTNAMELEN - 1] = '\0';
        opal_show_help("help-opal-shmem-sysv.txt", "sys call fail", 1, hn,
                       "shmat(2)", "", strerror(err), err);
        shmctl(ds_buf->seg_id, IPC_RMID, NULL);
        rc = OPAL_ERROR;
        goto out;
    }


    else if (0 != shmctl(ds_buf->seg_id, IPC_RMID, NULL)) {
        int err = errno;
        char hn[MAXHOSTNAMELEN];
        gethostname(hn, MAXHOSTNAMELEN - 1);
        hn[MAXHOSTNAMELEN - 1] = '\0';
        opal_show_help("help-opal-shmem-sysv.txt", "sys call fail", 1, hn,
                       "shmctl(2)", "", strerror(err), err);
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
             mca_shmem_sysv_component.super.base_version.mca_type_name,
             mca_shmem_sysv_component.super.base_version.mca_component_name,
             ds_buf->seg_id, (unsigned long)ds_buf->seg_size, ds_buf->seg_name)
        );
    }

out:


    if (OPAL_SUCCESS != rc) {

        if ((void *)-1 != seg_hdrp) {
            shmdt(seg_hdrp);
        }
        shmctl(ds_buf->seg_id, IPC_RMID, NULL);


        shmem_ds_reset(ds_buf);
    }
    return rc;
}
