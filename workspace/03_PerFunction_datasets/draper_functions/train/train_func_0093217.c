disp_format(SDL_Surface *sur)
{
    if ((sur = SDL_DisplayFormat(sur)) == 0) {
        fprintf(stderr, "ERR: ssur_displayformat: convertion failed\n");
        return 1;
    }
    return 0;
}
