r300DrawRectangle3D( void *drv, void *dev, DFBRectangle *rect )
{
     RadeonDriverData *rdrv = (RadeonDriverData*) drv;
     RadeonDeviceData *rdev = (RadeonDeviceData*) dev;
     float             x1, y1;
     float             x2, y2;
     u32              *v;

     x1 = rect->x;         y1 = rect->y;
     x2 = rect->x+rect->w; y2 = rect->y+rect->h;
     if (rdev->matrix) {
          float x, y;

          v = r300_init_vb( rdrv, rdev, VF_PRIM_TYPE_LINE_LOOP, 4, 32 );
          RADEON_TRANSFORM( x1, y1, x, y, rdev->matrix, rdev->affine_matrix );
          VTX( v, x, y, rdev->color );
          RADEON_TRANSFORM( x2, y1, x, y, rdev->matrix, rdev->affine_matrix );
          VTX( v, x, y, rdev->color );
          RADEON_TRANSFORM( x2, y2, x, y, rdev->matrix, rdev->affine_matrix );
          VTX( v, x, y, rdev->color );
          RADEON_TRANSFORM( x1, y2, x, y, rdev->matrix, rdev->affine_matrix );
          VTX( v, x, y, rdev->color );
     }
     else {
          v = r300_init_vb( rdrv, rdev, VF_PRIM_TYPE_LINE_LOOP, 4, 32 );
          VTX( v, x1, y1, rdev->color );
          VTX( v, x2, y1, rdev->color );
          VTX( v, x2, y2, rdev->color );
          VTX( v, x1, y2, rdev->color );
     }

     return true;
}
