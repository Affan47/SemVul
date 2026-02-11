Quit() {
    if(SDL_WasInit(SDL_INIT_AUDIO)) {
      SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }
  }
}
