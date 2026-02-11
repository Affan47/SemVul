mach64DoBlit2D( Mach64DriverData *mdrv,
                            Mach64DeviceData *mdev,
                            DFBRectangle *srect,
                            DFBRectangle *drect )
{
     volatile u8 *mmio = mdrv->mmio_base;

     u32 dst_cntl = 0;

     if (srect->x <= drect->x) {
          srect->x += srect->w - 1;
          drect->x += drect->w - 1;
     } else
          dst_cntl |= DST_X_DIR;

     if (srect->y <= drect->y) {
          srect->y += srect->h - 1;
          drect->y += drect->h - 1;
     } else
          dst_cntl |= DST_Y_DIR;

     mach64_waitfifo( mdrv, mdev, 5 );

     mach64_out32( mmio, SRC_Y_X, (S13( srect->x ) << 16) | S14( srect->y ) );
     mach64_out32( mmio, SRC_HEIGHT1_WIDTH1, (srect->w << 16) | srect->h );

     mach64_out32( mmio, DST_CNTL, dst_cntl );
     mach64_out32( mmio, DST_Y_X, (S13( drect->x ) << 16) | S14( drect->y ) );
     mach64_out32( mmio, DST_HEIGHT_WIDTH, (drect->w << 16) | drect->h );
}
