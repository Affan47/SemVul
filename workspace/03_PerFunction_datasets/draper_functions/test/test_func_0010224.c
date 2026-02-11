dfb_x11_image_destroy_handler( DFBX11 *x11, x11Image *image )
{
     D_MAGIC_ASSERT( image, x11Image );

     XLockDisplay( x11->display );

     XShmDetach( x11->display, &image->seginfo );

     XDestroyImage( image->ximage );

     XUnlockDisplay( x11->display );

     shmdt( image->seginfo.shmaddr );

     shmctl( image->seginfo.shmid, IPC_RMID, NULL );

     return DFB_OK;
}
