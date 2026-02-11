set_config_opt(int ch, const char *param, config_t * config)
{
    switch (ch) {

    case 'd':

        if (strcasecmp(param, "random") == 0)
            config->dither = dit_random;
        else if (strcasecmp(param, "diffusion") == 0)
            config->dither = dit_diffusion;
        else if (strcasecmp(param, "none") == 0)
            config->dither = dit_none;
        else {
            printf("unknown dithering mode: %s\n", param);
            exit(EXIT_FAILURE);
        }

        break;

    case 'c':

        config->client = ptoc_get_client(param);

        break;

    case 'f':

        config->font = ptoc_get_font(param);

        break;

    case 'x':

        config->resize = 1;
        config->newx = atoi(param);

        break;

    case 'y':

        config->resize = 1;
        config->newy = atoi(param);

        break;

    case 'w':

        config->pause = atoi(param);

        break;

    case '?':

        return (-1);
        break;
    }

    return (0);
}
