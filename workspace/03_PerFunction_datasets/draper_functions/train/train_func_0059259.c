mach64_fill_trapezoid( Mach64DriverData *mdrv,
                                   Mach64DeviceData *mdev,
                                   int X1l, int X1r,
                                   int X2l, int X2r,
                                   int Y, int dY )
{
     volatile u8 *mmio = mdrv->mmio_base;

     u32 dst_cntl;
     int   dXl, dXr;

     X1r++; X2r++;

     dst_cntl = DST_Y_DIR | TRAP_FILL_DIR;

     dXl = X2l - X1l;
     if (dXl < 0)
          dXl = -dXl;
     else
          dst_cntl |= DST_X_DIR;

     dXr = X2r - X1r;
     if (dXr < 0)
          dXr = -dXr;
     else
          dst_cntl |= TRAIL_X_DIR;

     mach64_waitfifo( mdrv, mdev, 9 );

     mach64_out32( mmio, DST_CNTL, dst_cntl );
     mach64_out32( mmio, DST_Y_X, (S13( X1l ) << 16) | S14( Y ) );

     mach64_out32( mmio, LEAD_BRES_ERR, -dY );
     mach64_out32( mmio, LEAD_BRES_INC,  2*dXl );
     mach64_out32( mmio, LEAD_BRES_DEC, -2*dY );

     mach64_out32( mmio, TRAIL_BRES_ERR, -dY );
     mach64_out32( mmio, TRAIL_BRES_INC,  2*dXr );
     mach64_out32( mmio, TRAIL_BRES_DEC, -2*dY );

     mach64_out32( mmio, LEAD_BRES_LNTH, (S14( X1r ) << 16) | (dY+1) | DRAW_TRAP | LINE_DIS );
}
