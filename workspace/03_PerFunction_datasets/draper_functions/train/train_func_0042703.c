i810_release_resource( I810DriverData *idrv, I810DeviceData *idev )
{
     agp_unbind unbind;

     if (idrv->flags & I810RES_STATE_SAVE) {
          i810_writel( idrv->mmio_base, LP_RING, idev->lring1 );
          i810_writel( idrv->mmio_base, LP_RING + RING_HEAD, idev->lring2 );
          i810_writel( idrv->mmio_base, LP_RING + RING_START, idev->lring3 );
          i810_writel( idrv->mmio_base, LP_RING + RING_LEN, idev->lring4 );
     }

     if (idrv->flags & I810RES_MMAP) {
          munmap((void *) idrv->aper_base, idev->info.aper_size * 1024 * 1024);
          idrv->flags &= ~I810RES_MMAP;
     }

     if (idrv->flags & I810RES_LRING_BIND) {
          unbind.key = idev->lring_bind.key;
          ioctl(idrv->agpgart, AGPIOC_UNBIND, &unbind);
     }

     if (idrv->flags & I810RES_LRING_ACQ)
          ioctl(idrv->agpgart, AGPIOC_DEALLOCATE, idev->lring_mem.key);

     if (idrv->flags & I810RES_OVL_BIND) {
          unbind.key = idev->ovl_bind.key;
          ioctl(idrv->agpgart, AGPIOC_UNBIND, &unbind);
     }

     if (idrv->flags & I810RES_OVL_ACQ)
          ioctl(idrv->agpgart, AGPIOC_DEALLOCATE, idev->ovl_mem.key);

     if (idrv->flags & I810RES_GART_ACQ) {
          ioctl(idrv->agpgart, AGPIOC_RELEASE);
          idrv->flags &= ~I810RES_GART_ACQ;
     }

     if (idrv->flags & I810RES_GART) {
          close(idrv->agpgart);
          idrv->flags &= ~I810RES_GART;
     }
}
