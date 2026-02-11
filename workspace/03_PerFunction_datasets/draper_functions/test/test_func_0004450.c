CreateSharedBackendStatus(void)
{
	Size		size = BackendStatusShmemSize();
	bool		found;


	BackendStatusArray = (PgBackendStatus *)
		ShmemInitStruct("Backend Status Array", size, &found);

	if (!found)
	{


		MemSet(BackendStatusArray, 0, size);
	}
}
