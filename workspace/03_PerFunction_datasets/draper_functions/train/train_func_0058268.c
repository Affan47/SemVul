driver_init_driver( CoreGraphicsDevice  *device,
                    GraphicsDeviceFuncs *funcs,
                    void                *driver_data,
                    void                *device_data,
                    CoreDFB             *core )
{
     NeoDriverData *ndrv = (NeoDriverData*) driver_data;

     ndrv->mmio_base = (volatile u8*) dfb_gfxcard_map_mmio( device, 0, -1 );
     if (!ndrv->mmio_base)
          return DFB_IO;

     switch (dfb_gfxcard_get_accelerator( device )) {

          case 95:
          case 96:
          case 97:
          case 98:
               return neo2200_init_driver( device, funcs, driver_data );
     }

     return DFB_BUG;
}
