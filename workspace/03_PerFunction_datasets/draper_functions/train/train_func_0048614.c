quit_sdl()
{
    if (sdl.screen) SDL_FreeSurface(sdl.screen);
    if ( empty_cursor ) SDL_FreeCursor( empty_cursor );
    if (sdl.vmodes) free(sdl.vmodes);
    SDL_Quit();
    printf("SDL finalized\n");
}
