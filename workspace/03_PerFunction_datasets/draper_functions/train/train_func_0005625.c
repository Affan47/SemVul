evas_software_xlib_x_output_buffer_free(X_Output_Buffer *xob, int psync)
{
   if (xob->shm_info)
     {
	if (psync) XSync(xob->display, False);
	XShmDetach(xob->display, xob->shm_info);
	XDestroyImage(xob->xim);
	shmdt(xob->shm_info->shmaddr);
	shmctl(xob->shm_info->shmid, IPC_RMID, 0);
	free(xob->shm_info);
     }
   else
     {
	if (xob->data) xob->xim->data = NULL;
	XDestroyImage(xob->xim);
     }
   free(xob);
}
