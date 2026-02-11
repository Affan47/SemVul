freescreen()
{
	if (!initok || !x_image) return;
	if ((char *)fb.ptr != (char *)x_image->data)
		free(fb.ptr);
#ifdef USE_XSHM
	if (x_useshm)
	{

		XSync(x_display, False);
		if (!XShmDetach(x_display, &x_shm))
			die ("XShmDetach failed\n");
		XSync(x_display, False);
		shmdt(x_shm.shmaddr);
		shmctl(x_shm.shmid, IPC_RMID, 0);
		x_image->data = NULL;
	}
#endif
	free(x_image);
	x_image = NULL;
	fb.ptr = NULL;
}
