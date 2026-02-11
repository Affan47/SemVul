movie_add_area( int x, int y, int w, int h )
{
  if( movie_paused ) {
    movie_start_frame();
    return;
  }
  head[0] = '$';
  head[1] = x;
  head[2] = y & 0xff;
  head[3] = y >> 8;
  head[4] = w;
  head[5] = h & 0xff;
  head[6] = h >> 8;
  fwrite_compr( head, 7, 1, of );
  movie_compress_area( x, y, w, h, 0 );
  movie_compress_area( x, y, w, h, 8 );
  if( fmf_screen == 'R' ) {
    movie_compress_area( x, y, w, h, 16 );
  }
  slice_no++;
}
