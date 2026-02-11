init( GUIOptions &opts ) {
  View *view = NULL;
  Font *f1 = NULL, *f2 = NULL;
  Surface *icons = NULL;
  bool ok = false;

  if ( SDL_Init( SDL_INIT_VIDEO ) >= 0 ) {


    if ( !init_locale() ) return NULL;

    string datpath( get_data_dir() );
    datpath.append( CF_DATFILE );
    File datfile( datpath );
    if ( datfile.Open( "rb" ) ) {

      icons = new Surface;
      if ( !icons->LoadImageData( datfile ) ) {

        set_icon( *icons, Rect(64, 0, 32, 32) );

        view = new View( opts.px_width, opts.px_height, opts.bpp,
                         opts.sdl_flags );
        if ( view->s_surface && !TTF_Init()) {
          int smallsize, largesize;


          if ((opts.px_width <= 240) || (opts.px_height <= 320)) {
            smallsize = CF_FONT_LOWRES_SMALL;
            largesize = CF_FONT_LOWRES_LARGE;
          } else {
            smallsize = CF_FONT_SMALL;
            largesize = CF_FONT_LARGE;
          }

          datpath = get_data_dir() + CF_FONT;
          f1 = new Font();
          f2 = new Font();

          if ( !f1->Load( datpath.c_str(), smallsize ) &&
               !f2->Load( datpath.c_str(), largesize ) )
            ok = true;
          else cerr << "Error: Couldn't load font " << datpath << endl;
        } else cerr << "Error: Couldn't set video mode (" << SDL_GetError() << ')' << endl;

      } else cerr << "Error: Couldn't read data file" << endl;
    } else cerr << "Error: Couldn't open " << datpath << endl;
  } else cerr << "Error: Couldn't initialize ( " << SDL_GetError() << ')' << endl;

  if ( ok ) {

    SDL_WM_SetCaption( PROGRAMNAME, PROGRAMNAME );
    SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL );

    srand( time(0) );

    Audio::InitSfx( opts.sfx, opts.sfx_vol );
    Audio::InitMusic( opts.music, opts.music_vol );

    Network::Init();

    for ( int i = 0; i <= XP_MAX_LEVEL; ++i )
      Images[ICON_XP_BASE+i] = new Image( icons, 64 + i * XP_ICON_WIDTH, 32, XP_ICON_WIDTH, XP_ICON_HEIGHT );

    icons->DisplayFormat();

    view->SetSmallFont( f1 );
    view->SetLargeFont( f2 );
    view->SetFGPen( Color(CF_COLOR_HIGHLIGHT) );
    view->SetBGPen( Color(CF_COLOR_SHADOW) );
    view->SetEventFilter( event_filter );
    view->SetSystemIcons( icons );


    create_config_dir();

    return view;
  } else {
    delete icons;
    delete view;
    delete f1;
    delete f2;
    return NULL;
  }
}
