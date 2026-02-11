uc_probe_fbdev(UcDriverData *ucdrv)
{
     struct fb_flip flip;
     FBDev *dfb_fbdev = dfb_system_data();
     flip.device = VIAFB_FLIP_NOP;
     if (ioctl(dfb_fbdev->fd, FBIO_FLIPONVSYNC, &flip) == 0)
          ucdrv->canfliponvsync = true;
     else
          ucdrv->canfliponvsync = false;
}
