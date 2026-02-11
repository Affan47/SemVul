dfb_fbdev_set_mode( const VideoMode         *mode,
                    CoreSurface             *surface,
                    unsigned int             xoffset,
                    unsigned int             yoffset )
{
     DFBResult                  ret;
     struct fb_var_screeninfo   var;
     FBDevShared               *shared     = dfb_fbdev->shared;
     DFBDisplayLayerBufferMode  buffermode = DLBM_FRONTONLY;
     const CoreSurfaceConfig   *config     = &surface->config ;

     D_DEBUG_AT( FBDev_Mode, "%s( mode: %p, config: %p )\n", __FUNCTION__, mode, config );

     D_ASSERT( mode != NULL );
     D_ASSERT( config != NULL );

     switch (num_video_buffers( surface )) {
     case 3:
          buffermode = DLBM_TRIPLE;
          break;
     case 2:
          buffermode = DLBM_BACKVIDEO;
          break;
     case 1:
          buffermode = DLBM_FRONTONLY;
          break;
     default:
          D_BUG( "dfb_fbdev_set_mode() called with %d video buffers!", num_video_buffers( surface ) );
          return DFB_BUG;
     }

     ret = dfb_fbdev_mode_to_var( mode, config->format, config->size.w, config->size.h,
                                  xoffset, yoffset, buffermode, &var );
     if (ret) {
          D_ERROR( "FBDev/Mode: Failed to switch to %dx%d %s (buffermode %d)\n",
                   config->size.w, config->size.h, dfb_pixelformat_name(config->format), buffermode );
          return ret;
     }


     dfb_gfxcard_lock( GDLF_WAIT | GDLF_SYNC | GDLF_RESET | GDLF_INVALIDATE );

     if (FBDEV_IOCTL( FBIOPUT_VSCREENINFO, &var ) < 0) {
          int erno = errno;

          dfb_gfxcard_unlock();

          D_DEBUG_AT( FBDev_Mode, "  => FAILED!\n" );

          D_ERROR( "FBDev/Mode: Failed to switched to %dx%d (virtual %dx%d) at %d bit (%s)!\n",
                   var.xres, var.yres, var.xres_virtual, var.yres_virtual, var.bits_per_pixel,
                   dfb_pixelformat_name(config->format) );

          return errno2result( erno );
     }

     D_DEBUG_AT( FBDev_Mode, "  => SUCCESS\n" );

     shared->current_var = var;
     dfb_fbdev_var_to_mode( &var, &shared->current_mode );


     FBDEV_IOCTL( FBIOGET_FSCREENINFO, &shared->fix );

     D_INFO( "FBDev/Mode: Switched to %dx%d (virtual %dx%d) at %d bit (%s), pitch %d\n",
             var.xres, var.yres, var.xres_virtual, var.yres_virtual, var.bits_per_pixel,
             dfb_pixelformat_name(config->format), shared->fix.line_length );

     if (config->format == DSPF_RGB332)
          dfb_fbdev_set_rgb332_palette();
     else
          dfb_fbdev_set_gamma_ramp( config->format );


     shared->orig_var.xoffset = 0;
     shared->orig_var.yoffset = 0;

     dfb_surfacemanager_adjust_heap_offset( dfb_fbdev->shared->manager,
                                            var.yres_virtual * shared->fix.line_length );

     dfb_gfxcard_after_set_var();

     dfb_gfxcard_unlock();

     return DFB_OK;
}
