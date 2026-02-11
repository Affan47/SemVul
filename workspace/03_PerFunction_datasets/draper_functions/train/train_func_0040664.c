ovlSetColorAdjustment( CoreLayer          *layer,
                       void               *driver_data,
                       void               *layer_data,
                       DFBColorAdjustment *adj )
{

     if (iopl(3) < 0) {
          D_PERROR( "NeoMagic/Overlay: Could not change I/O permission level!\n" );
          return DFB_UNSUPPORTED;
     }

     neo_unlock();
     OUTGR(0xc4, (signed char)((adj->brightness >> 8) -128));
     neo_lock();

     return DFB_OK;
}
