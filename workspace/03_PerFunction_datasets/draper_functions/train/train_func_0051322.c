dfb_x11_image_init_handler( DFBX11 *x11, x11Image *image )
{
     Visual *visual;
     XImage *ximage;

     D_MAGIC_ASSERT( image, x11Image );

     if (!x11->use_shm)
          return DFB_UNSUPPORTED;


     visual = x11->visuals[DFB_PIXELFORMAT_INDEX(image->format)];
     if (!visual)
          return DFB_UNSUPPORTED;

     image->visual = visual;

     XLockDisplay( x11->display );

     ximage = XShmCreateImage( x11->display, image->visual, image->depth,
                               ZPixmap, NULL, &image->seginfo, image->width, image->height );
     if (!ximage) {
          D_ERROR( "X11/ShmImage: Error creating shared image (XShmCreateImage)!\n");
          XUnlockDisplay( x11->display );
          return DFB_FAILURE;
     }


     image->seginfo.shmid = shmget( IPC_PRIVATE,
                                    ximage->bytes_per_line * ximage->height,
                                    IPC_CREAT | 0777 );
     if (image->seginfo.shmid < 0)
          goto error;


     image->seginfo.shmaddr = shmat( image->seginfo.shmid, NULL, 0 );
     if (!image->seginfo.shmaddr)
          goto error_shmat;

     ximage->data = image->seginfo.shmaddr;


     image->seginfo.readOnly = False;

     if (!XShmAttach( x11->display, &image->seginfo ))
          goto error_xshmattach;

     image->ximage = ximage;
     image->pitch  = ximage->bytes_per_line;

     XUnlockDisplay( x11->display );

     return DFB_OK;


error_xshmattach:
     shmdt( image->seginfo.shmaddr );

error_shmat:
     shmctl( image->seginfo.shmid, IPC_RMID, NULL );

error:
     XDestroyImage( ximage );

     XUnlockDisplay( x11->display );

     return DFB_FAILURE;
}
