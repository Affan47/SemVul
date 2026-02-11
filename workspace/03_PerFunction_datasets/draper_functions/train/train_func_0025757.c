open_snd( void )
{
  char *ext;
  typedef struct {
    type_t type;
    const char *extension;
  } ext_t;

  int i;
  ext_t snd_ext_tab[] = {
    { TYPE_WAV,  "wav" },
    { TYPE_AU,   "au"  },
    { TYPE_AU,   "snd" },
    { TYPE_AIFF, "aif" },
    { TYPE_AIFF, "aiff" },
    { TYPE_FFMPEG, "mp2" },
    { TYPE_FFMPEG, "mp3" },
    { TYPE_FFMPEG, "ogg" },
    { TYPE_FFMPEG, "aac" },
    { TYPE_FFMPEG, "ac3" },
    { TYPE_FFMPEG, "m4a" },
    { 0, NULL }
  };

  const char *snd_tstr[] = {
    "FFMPEG - ffmpeg file format",
    "WAV - MS Wave format",
    "AU - SUN OS audio file format",
    "AIF - MAC/OS audio file"
  };

  if( do_info ) return 0;

  if( snd_name ) {
    if( ( snd = fopen( snd_name, "wb" ) ) == NULL ) {
      printe( "Cannot open sound file '%s'...\n", snd_name );
      return ERR_OPEN_SND;
    }
  } else if( out_t == TYPE_FFMPEG ) {
    snd_t = TYPE_FFMPEG;
    return 0;
  } else {
    snd_t = TYPE_NONE;
    return 0;
  }
  if( snd_t == TYPE_UNSET ) {
    snd_t = TYPE_WAV;
    ext = find_filename_ext( snd_name );
    for( i = 0; ext != NULL && snd_ext_tab[i].extension != NULL; i++ ) {
      if( !strcasecmp( ext, snd_ext_tab[i].extension ) ) {
        snd_t = snd_ext_tab[i].type;
        break;
      }
    }
  }
  printi( 0, "open_snd(): Sound file (%s) opened as %s file.\n", snd_name,
          snd_tstr[snd_t - TYPE_FFMPEG] );
  return 0;
}
