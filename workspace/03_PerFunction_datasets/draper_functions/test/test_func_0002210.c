driver_init_driver( CoreGraphicsDevice  *device,
                    GraphicsDeviceFuncs *funcs,
                    void                *driver_data,
                    void                *device_data,
                    CoreDFB             *core )
{
     DFBResult       ret;
     I830DriverData *idrv = driver_data;
     I830DeviceData *idev = device_data;

     idrv->idev = device_data;

     idrv->mmio_base = (volatile u8*) dfb_gfxcard_map_mmio( device, 0, -1 );
     if (!idrv->mmio_base)
          return DFB_IO;

     ret = i830_agp_setup( device, idrv, idev );
     if (ret) {
          dfb_gfxcard_unmap_mmio( device, idrv->mmio_base, -1 );
          return ret;
     }

     idrv->info = idev->info;

     funcs->CheckState         = i830CheckState;
     funcs->SetState           = i830SetState;
     funcs->EngineSync         = i830EngineSync;
     funcs->FlushTextureCache  = i830FlushTextureCache;

     dfb_layers_register( dfb_screens_at(DSCID_PRIMARY), driver_data, &i830OverlayFuncs );

     return DFB_OK;
}
