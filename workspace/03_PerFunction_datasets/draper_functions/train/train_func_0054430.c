InternalIpcMemoryCreate(IpcMemoryKey memKey, Size size)
{
	IpcMemoryId shmid;
	void	   *memAddress;

	shmid = shmget(memKey, size, IPC_CREAT | IPC_EXCL | IPCProtection);

	if (shmid < 0)
	{


		if (errno == EEXIST || errno == EACCES
#ifdef EIDRM
			|| errno == EIDRM
#endif
			)
			return NULL;


		if (errno == EINVAL)
		{
			int		save_errno = errno;

			shmid = shmget(memKey, 0, IPC_CREAT | IPC_EXCL | IPCProtection);

			if (shmid < 0)
			{

				if (errno == EEXIST || errno == EACCES
#ifdef EIDRM
					|| errno == EIDRM
#endif
					)
					return NULL;

			}
			else
			{


				if (shmctl(shmid, IPC_RMID, NULL) < 0)
					elog(LOG, "shmctl(%d, %d, 0) failed: %m",
						 (int) shmid, IPC_RMID);
			}

			errno = save_errno;
		}


		ereport(FATAL,
				(errmsg("could not create shared memory segment: %m"),
		  errdetail("Failed system call was shmget(key=%lu, size=%lu, 0%o).",
					(unsigned long) memKey, (unsigned long) size,
					IPC_CREAT | IPC_EXCL | IPCProtection),
				 (errno == EINVAL) ?
				 errhint("This error usually means that PostgreSQL's request for a shared memory "
		  "segment exceeded your kernel's SHMMAX parameter.  You can either "
						 "reduce the request size or reconfigure the kernel with larger SHMMAX.  "
				  "To reduce the request size (currently %lu bytes), reduce "
			   "PostgreSQL's shared_buffers parameter (currently %d) and/or "
						 "its max_connections parameter (currently %d).\n"
						 "If the request size is already small, it's possible that it is less than "
						 "your kernel's SHMMIN parameter, in which case raising the request size or "
						 "reconfiguring SHMMIN is called for.\n"
		"The PostgreSQL documentation contains more information about shared "
						 "memory configuration.",
						 (unsigned long) size, NBuffers, MaxBackends) : 0,
				 (errno == ENOMEM) ?
				 errhint("This error usually means that PostgreSQL's request for a shared "
				   "memory segment exceeded available memory or swap space. "
				  "To reduce the request size (currently %lu bytes), reduce "
			   "PostgreSQL's shared_buffers parameter (currently %d) and/or "
						 "its max_connections parameter (currently %d).\n"
		"The PostgreSQL documentation contains more information about shared "
						 "memory configuration.",
						 (unsigned long) size, NBuffers, MaxBackends) : 0,
				 (errno == ENOSPC) ?
				 errhint("This error does *not* mean that you have run out of disk space. "
						 "It occurs either if all available shared memory IDs have been taken, "
						 "in which case you need to raise the SHMMNI parameter in your kernel, "
		  "or because the system's overall limit for shared memory has been "
				 "reached.  If you cannot increase the shared memory limit, "
		  "reduce PostgreSQL's shared memory request (currently %lu bytes), "
			"by reducing its shared_buffers parameter (currently %d) and/or "
						 "its max_connections parameter (currently %d).\n"
		"The PostgreSQL documentation contains more information about shared "
						 "memory configuration.",
						 (unsigned long) size, NBuffers, MaxBackends) : 0));
	}


	on_shmem_exit(IpcMemoryDelete, Int32GetDatum(shmid));


	memAddress = shmat(shmid, NULL, PG_SHMAT_FLAGS);

	if (memAddress == (void *) -1)
		elog(FATAL, "shmat(id=%d) failed: %m", shmid);


	on_shmem_exit(IpcMemoryDetach, PointerGetDatum(memAddress));


	RecordSharedMemoryInLockFile((unsigned long) memKey,
								 (unsigned long) shmid);

	return memAddress;
}
