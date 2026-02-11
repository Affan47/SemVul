OpenAllJoysticks(void)
{
    int i;
    int num_joysticks;
    int result;

    if (!joystick_initted)
    {
        return 0;
    }


    num_joysticks = SDL_NumJoysticks();

    all_joysticks = malloc(sizeof(SDL_Joystick *) * num_joysticks);

    result = 0;

    for (i=0; i<num_joysticks; ++i)
    {
        all_joysticks[i] = SDL_JoystickOpen(i);


        if (all_joysticks[i] != NULL)
        {
            result = 1;
        }
    }


    if (result)
    {
        SDL_JoystickEventState(SDL_ENABLE);
    }
    else
    {
        free(all_joysticks);
        all_joysticks = NULL;
    }

    return result;
}
