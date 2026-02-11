sprite_load_surface(const char *filename) {
    SDL_Surface *ret = IMG_Load(filename);
    if (!ret)
        die("Cannot load file %s: %s", filename, SDL_GetError());
    return ret;
}
