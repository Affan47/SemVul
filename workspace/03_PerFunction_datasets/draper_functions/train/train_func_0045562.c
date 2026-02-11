opus_6821_access( libspectrum_byte reg, libspectrum_byte data,
                  libspectrum_byte dir )
{
  int drive, side;
  int i;

  switch( reg & 0x03 ) {
  case 0:
    if( dir ) {
      if( control_a & 0x04 ) {
        data_reg_a = data;

        drive = ( data & 0x02 ) == 2 ? 1 : 0;
        side = ( data & 0x10 )>>4 ? 1 : 0;

        for( i = 0; i < OPUS_NUM_DRIVES; i++ ) {
          fdd_set_head( &opus_drives[ i ].fdd, side );
        }

        fdd_select( &opus_drives[ (!drive) ].fdd, 0 );
        fdd_select( &opus_drives[ drive ].fdd, 1 );

        if( opus_fdc->current_drive != &opus_drives[ drive ] ) {
          if( opus_fdc->current_drive->fdd.motoron ) {
            fdd_motoron( &opus_drives[ (!drive) ].fdd, 0 );
            fdd_motoron( &opus_drives[ drive ].fdd, 1 );
          }
          opus_fdc->current_drive = &opus_drives[ drive ];
        }
      } else {
        data_dir_a = data;
      }
    } else {
      if( control_a & 0x04 ) {

        data_reg_a &= ~0x40;
        return data_reg_a;
      } else {
        return data_dir_a;
      }
    }
    break;
  case 1:
    if( dir ) {
      control_a = data;
    } else {

      return control_a | 0x40;
    }
    break;
  case 2:
    if( dir ) {
      if( control_b & 0x04 ) {
        data_reg_b = data;
        printer_parallel_write( 0x00, data );


        printer_parallel_strobe_write( 0 );
        printer_parallel_strobe_write( 1 );
        printer_parallel_strobe_write( 0 );
      } else {
        data_dir_b = data;
      }
    } else {
      if( control_b & 0x04 ) {
        return data_reg_b;
      } else {
        return data_dir_b;
      }
    }
    break;
  case 3:
    if( dir ) {
      control_b = data;
    } else {
      return control_b;
    }
    break;
  }

  return 0;
}
