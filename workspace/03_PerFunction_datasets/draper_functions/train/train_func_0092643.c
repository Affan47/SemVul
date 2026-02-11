video_resize(int w, int h) {
    if (w < 320 || h < 200)
        return;
    screen = SDL_SetVideoMode(w, h, 0, flags);
    if (!screen)
        die("couldn't change resolution. sorry");
}
