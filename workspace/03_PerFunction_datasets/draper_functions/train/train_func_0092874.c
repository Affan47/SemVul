r200DoTextureTriangles( RadeonDriverData *rdrv, RadeonDeviceData *rdev,
                        DFBVertex *ve, int num, u32 primitive )
{
     volatile u8 *mmio = rdrv->mmio_base;
     int          i;

     radeon_waitfifo( rdrv, rdev, 1 );

     radeon_out32( mmio, SE_VF_CNTL, primitive | VF_PRIM_WALK_DATA |
                                     (num << VF_NUM_VERTICES_SHIFT) );

     for (; num >= 10; num -= 10) {
          radeon_waitfifo( rdrv, rdev, 60 );
          for (i = 0; i < 10; i++) {
               radeon_out32( mmio, SE_PORT_DATA0, f2d(ve[i].x) );
               radeon_out32( mmio, SE_PORT_DATA0, f2d(ve[i].y) );
               radeon_out32( mmio, SE_PORT_DATA0, f2d(ve[i].z) );
               radeon_out32( mmio, SE_PORT_DATA0, f2d(ve[i].w) );
               radeon_out32( mmio, SE_PORT_DATA0, f2d(ve[i].s) );
               radeon_out32( mmio, SE_PORT_DATA0, f2d(ve[i].t) );
          }
          ve += 10;
     }

     if (num > 0) {
          radeon_waitfifo( rdrv, rdev, num*6 );
          for (i = 0; i < num; i++) {
               radeon_out32( mmio, SE_PORT_DATA0, f2d(ve[i].x) );
               radeon_out32( mmio, SE_PORT_DATA0, f2d(ve[i].y) );
               radeon_out32( mmio, SE_PORT_DATA0, f2d(ve[i].z) );
               radeon_out32( mmio, SE_PORT_DATA0, f2d(ve[i].w) );
               radeon_out32( mmio, SE_PORT_DATA0, f2d(ve[i].s) );
               radeon_out32( mmio, SE_PORT_DATA0, f2d(ve[i].t) );
          }
     }
}
