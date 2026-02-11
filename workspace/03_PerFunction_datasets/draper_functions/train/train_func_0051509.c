primaryGetScreenSize( CoreScreen *screen,
                      void       *driver_data,
                      void       *screen_data,
                      int        *ret_width,
                      int        *ret_height )
{
     D_ASSERT( dfb_fbdev != NULL );
     D_ASSERT( dfb_fbdev->shared != NULL );

     *ret_width  = dfb_fbdev->shared->current_mode.xres;
     *ret_height = dfb_fbdev->shared->current_mode.yres;

     return DFB_OK;
}
