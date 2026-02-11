lam_cleanup_objects(void)
{
    int			sysvid;
    char		type;
    char		obj[MAXPATHLEN];

    if (set_names("lam_cleanup_objects") == LAMERROR)
      return;
    if (lock_registry("lam_cleanup_objects") == LAMERROR)
      return;


    if ((f = fopen(reg_fname, "r")) == 0) {
	if (errno != ENOENT) {
	    clean_warning("lam_cleanup_objects (fopen)");
	}
    } else {
      while (fscanf(f, "%c %s\n", &type, obj) == 2) {


	switch (type) {
#if LAM_HAVE_SYSV_SHMEM
	case 'm':
	    sysvid = atoi(obj);
	    shmctl(sysvid, IPC_RMID, (struct shmid_ds *) 0);
	    break;
#endif
#if LAM_HAVE_SYSV_SEMAPHORES
	case 's':
	    sysvid = atoi(obj);
	    semctl(sysvid, 0, IPC_RMID, semctl_arg);
	    break;
#endif
	case 'f':
	    unlink(obj);
	    break;
	default:
	    break;
	}
      }

      fclose(f);
      f = 0;

      unlink(reg_fname);
    }

    unlock_registry();
    free_filenames();
}
