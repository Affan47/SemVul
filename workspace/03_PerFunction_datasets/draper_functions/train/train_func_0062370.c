bothPressed() const {
    Uint8 ms = SDL_GetMouseState(0,0);
    return (ms & SDL_BUTTON(SDL_BUTTON_RIGHT) && ms & SDL_BUTTON(SDL_BUTTON_LEFT));
}
