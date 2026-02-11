maven_enable( MatroxMavenData  *mav,
              MatroxDriverData *mdrv )
{
     MatroxDeviceData *mdev = mdrv->device_data;
     bool              ntsc = dfb_config->matrox_tv_std != DSETV_PAL;

     if (mdev->g450_matrox) {
          if (dfb_config->matrox_cable == 1)

               maven_write_byte( mav, mdrv, 0x80, ntsc ? 0x43 : 0x41 );
          else

               maven_write_byte( mav, mdrv, 0x80, ntsc ? 0x03 : 0x01 );
     }
     else
          maven_write_byte( mav, mdrv, 0x82, 0x20 );

     maven_write_byte( mav, mdrv, 0x3E, 0x00 );
}
