dfb_fbdev_test_mode( const VideoMode             *mode,
                     const CoreLayerRegionConfig *config )
{
     DFBResult                  ret;
     struct fb_var_screeninfo   var;
     FBDevShared               *shared = dfb_fbdev->shared;
     const DFBRectangle        *source = &config->source;

     D_DEBUG_AT( FBDev_Mode, "%s( mode: %p, config: %p )\n", __FUNCTION__, mode, config );

     D_ASSERT( mode != NULL );
     D_ASSERT( config != NULL );


     if (source->w != mode->xres && shared->fix.xpanstep == 0)
          return DFB_UNSUPPORTED;
     if (source->h != mode->yres && shared->fix.ypanstep == 0 && shared->fix.ywrapstep == 0)
          return DFB_UNSUPPORTED;

     ret = dfb_fbdev_mode_to_var( mode, config->format, config->width, config->height,
                                  0, 0, config->buffermode, &var );
     if (ret)
          return ret;


     var.activate = FB_ACTIVATE_TEST;


     dfb_gfxcard_lock( GDLF_WAIT | GDLF_SYNC | GDLF_RESET | GDLF_INVALIDATE );

     if (FBDEV_IOCTL( FBIOPUT_VSCREENINFO, &var ) < 0) {
          int erno = errno;
          dfb_gfxcard_unlock();
          D_DEBUG_AT( FBDev_Mode, "  => FAILED!\n" );
          return errno2result( erno );
     }

     dfb_gfxcard_unlock();

     D_DEBUG_AT( FBDev_Mode, "  => SUCCESS\n" );

     return DFB_OK;
}
