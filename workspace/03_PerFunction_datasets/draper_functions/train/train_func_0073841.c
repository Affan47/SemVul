display_dirty_flashing_timex(void)
{
  libspectrum_word offset;
  libspectrum_byte *screen, attr;

  screen = RAM[ memory_current_screen ];

  if( !scld_last_dec.name.hires ) {
    if( scld_last_dec.name.b1 ) {

      for( offset = ALTDFILE_OFFSET; offset < 0x3800; offset++ ) {
        attr = screen[ offset ];
        if( attr & 0x80 ) display_dirty8( offset - ALTDFILE_OFFSET );
      }

    } else if( scld_last_dec.name.altdfile ) {

      for( offset= 0x3800; offset < 0x3b00; offset++ ) {
        attr = screen[ offset ];
        if( attr & 0x80 ) display_dirty64( offset - ALTDFILE_OFFSET );
      }

    } else {

      display_dirty_flashing_sinclair();

    }
  }
}
