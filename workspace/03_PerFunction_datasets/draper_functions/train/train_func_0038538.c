SetSDLVideoDriver(void)
{


    if (strcmp(video_driver, "") != 0)
    {
        char *env_string;

        env_string = malloc(strlen(video_driver) + 30);
        sprintf(env_string, "SDL_VIDEODRIVER=%s", video_driver);
        putenv(env_string);
        free(env_string);
    }
}
