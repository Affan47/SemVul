driver_init_device( CoreGraphicsDevice *device,
                    GraphicsDeviceInfo *device_info,
                    void               *driver_data,
                    void               *device_data )
{
     Mach64DriverData *mdrv = (Mach64DriverData*) driver_data;
     Mach64DeviceData *mdev = (Mach64DeviceData*) device_data;
     volatile u8      *mmio = mdrv->mmio_base;


     device_info->caps.flags = CCF_CLIPPING;

     switch (mdrv->accelerator) {
          case FB_ACCEL_ATI_MACH64GT:
               device_info->caps.drawing  = MACH64GT_SUPPORTED_DRAWINGFLAGS;
               device_info->caps.blitting = MACH64GT_SUPPORTED_BLITTINGFLAGS;
               device_info->caps.accel    = MACH64GT_SUPPORTED_DRAWINGFUNCTIONS |
                                            MACH64GT_SUPPORTED_BLITTINGFUNCTIONS;
               break;
          default:
               device_info->caps.drawing  = MACH64_SUPPORTED_DRAWINGFLAGS;
               device_info->caps.blitting = MACH64_SUPPORTED_BLITTINGFLAGS;
               device_info->caps.accel    = MACH64_SUPPORTED_DRAWINGFUNCTIONS |
                                            MACH64_SUPPORTED_BLITTINGFUNCTIONS;
               break;
     }

     switch (mdrv->accelerator) {
          case FB_ACCEL_ATI_MACH64GX:
               snprintf( device_info->name,
                         DFB_GRAPHICS_DEVICE_INFO_NAME_LENGTH, "Mach64 GX" );
               break;
          case FB_ACCEL_ATI_MACH64CT:
               snprintf( device_info->name,
                         DFB_GRAPHICS_DEVICE_INFO_NAME_LENGTH, "Mach64 CT" );
               break;
          case FB_ACCEL_ATI_MACH64VT:
               mdev->chip = mach64_chip_type_vt( mdrv, device_info );
               break;
          case FB_ACCEL_ATI_MACH64GT:
               mdev->chip = mach64_chip_type_gt( mdrv, device_info );


               device_info->limits.surface_max_power_of_two_pixelpitch = 1024;
               device_info->limits.surface_max_power_of_two_height     = 1024;
               break;
     }

     snprintf( device_info->vendor,
               DFB_GRAPHICS_DEVICE_INFO_VENDOR_LENGTH, "ATI" );

     device_info->limits.surface_byteoffset_alignment = 8;
     device_info->limits.surface_bytepitch_alignment  = 16;
     device_info->limits.surface_pixelpitch_alignment = 8;


     if (mdev->chip >= CHIP_3D_RAGE_PRO) {
          mdev->hw_debug = mach64_in32( mmio, HW_DEBUG );


          mdev->hw_debug_orig = mdev->hw_debug;


          mdev->hw_debug &= ~(AUTO_FF_DIS | INTER_PRIM_DIS);

          if ((mach64_in32( mmio, CONFIG_STAT0 ) & CFG_MEM_TYPE) == CFG_MEM_TYPE_SGRAM) {

               mdev->hw_debug &= ~(AUTO_BLKWRT_DIS | AUTO_BLKWRT_COLOR_DIS);

               device_info->limits.surface_byteoffset_alignment = 64;
               device_info->limits.surface_bytepitch_alignment  = 64;
          }
     }

     return DFB_OK;
}
