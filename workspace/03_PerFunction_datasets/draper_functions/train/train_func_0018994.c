set_border( int y, int start, int end, int colour )
{
  libspectrum_dword chunk_detail = colour << 11;
  int index = start + y * DISPLAY_SCREEN_WIDTH_COLS;

  for( ; start < end; start++ ) {


    if( display_last_screen[ index ] != chunk_detail ) {
      uidisplay_plot8( start, y, 0x00, 0, colour );


      display_last_screen[ index ] = chunk_detail;


      display_is_dirty[y] |= ( (libspectrum_qword)1 << start );
    }
    index++;
  }
}
