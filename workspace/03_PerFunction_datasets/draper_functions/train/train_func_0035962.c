png_load( char *path )
{
    SDL_RWops *src;
    SDL_Surface *surf;
    if ( ( src = SDL_RWFromFile(path, "rb") ) == 0 ) {
        fprintf( stderr, "%s\n", SDL_GetError() );
        return 0;
    }
    else {
        surf = IMG_LoadPNG_RW( src );
        SDL_RWclose( src );
        return surf;
    }
}
