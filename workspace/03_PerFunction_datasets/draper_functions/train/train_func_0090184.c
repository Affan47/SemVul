setCaption(const std::string &title)
{
    bool done = false;
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    if (SDL_GetWMInfo(&info) > 0) {
        done = sysSetCaption(&info, title);
    }

    if (!done) {
        SDL_WM_SetCaption(title.c_str(), NULL);
    }
}
