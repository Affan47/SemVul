find_input_dev (void)
{
    FILE *fp = NULL;
    signed char have_evdev = -2;

    fp = fopen (INPUT_DEVICES, "r");

    if (!fp)
        return -1;

    while (!feof (fp))
    {
        char *buff = NULL;
        size_t len = 0;
        short int number = -2;
        getline (&buff, &len, fp);
        sscanf (buff, "H: Handlers=kbd event%hu", &number);
        free (buff);
        if (number > -1)
        {
            have_evdev = number;
            break;
        }
    }

    fclose (fp);

    return have_evdev;
}
