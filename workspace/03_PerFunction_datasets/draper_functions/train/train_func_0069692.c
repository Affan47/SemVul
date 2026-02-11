open_inp( void )
{
  if( inp_file ) {
    if( inp_file != stdin ) {
      fclose( inp_file );
    } else {
      do_now = DO_EOP;
      return 0;
    }
  }
  if( inp_name ) {
    if( ( inp_file = fopen( inp_name, "rb" ) ) == NULL ) {
      printe( "Cannot open input file '%s'...\n", inp_name );
      return ERR_OPEN_INP;
    }
  } else if( out_t == TYPE_FFMPEG ) {
    snd_t = TYPE_FFMPEG;
    return 0;
  } else {
    inp_file = stdin;
    inp_name = "(-=stdin=-)";
  }
  if( fseek( inp_file, 0, SEEK_END ) == -1 ) {
    printi( 4, "open_inp(): cannot seek to the end of the input file (not seekable).\n" );
    inp_ftell = 0;
  } else if( ( inp_ftell = ftell( inp_file ) ) == -1 ) {
    printi( 4, "open_inp(): cannot ftell input file??.\n" );
    fseek( inp_file, 0, SEEK_SET );
    inp_ftell = 0;
  } else {
    fseek( inp_file, 0, SEEK_SET );
  }

  if( inp_t == TYPE_UNSET ) {
    fread_buff( fhead, 4, INTO_BUFF );
    if( memcmp( fhead, "FMF_", 4 ) == 0 )
      inp_t = TYPE_FMF;
    else
      inp_t = TYPE_SCR;
  }
  do_now = inp_t == TYPE_FMF ? DO_HEAD : DO_SLICE;
  printi( 0, "open_inp(): Input file (%s) opened as %s file.\n", inp_name,
          inp_t == TYPE_FMF ? "FMF" : "SCR" );
  return 0;
}
