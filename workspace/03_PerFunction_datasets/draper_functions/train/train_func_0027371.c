movie_stop( void )
{
  if( !movie_paused && !movie_recording ) return;

  fwrite_compr( "X", 1, 1, of );
#ifdef HAVE_ZLIB_H
  {
    if( fmf_compr != 0 ) {
      zstream.avail_in = 0;
      do {
        zstream.avail_out = ZBUF_SIZE;
        zstream.next_out = zbuf_o;
        deflate( &zstream, Z_SYNC_FLUSH );
        if( zstream.avail_out != ZBUF_SIZE )
          fwrite( zbuf_o, ZBUF_SIZE - zstream.avail_out, 1, of );
      } while ( zstream.avail_out != ZBUF_SIZE );
      deflateEnd( &zstream );
      fmf_compr = -1;
    }
  }
#endif
  format = '?';
  if( of ) {
    fclose( of );
    of = NULL;
  }
#ifdef MOVIE_DEBUG_PRINT
  fprintf( stderr, "Debug movie: saved %d.%d frame(.slice)\n", frame_no, slice_no );
#endif
  movie_recording = 0;
  movie_paused = 0;
  ui_menu_activate( UI_MENU_ITEM_FILE_MOVIE_RECORDING, 0 );
}
