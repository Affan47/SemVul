I_FindScreenMode(int w, int h)
{
    screen_mode_t **modes_list;
    screen_mode_t *best_mode;
    int modes_list_length;
    int num_pixels;
    int best_num_pixels;
    int i;


    if (fullscreen)
    {
        if (w == SCREENWIDTH && h == SCREENHEIGHT)
        {
            return &mode_scale_1x;
        }
        else if (w == SCREENWIDTH*2 && h == SCREENHEIGHT*2)
        {
            return &mode_scale_2x;
        }
    }

    GetScreenModes(&modes_list, &modes_list_length);


    best_mode = NULL;
    best_num_pixels = 0;

    for (i=0; i<modes_list_length; ++i)
    {


        if (modes_list[i]->width > w || modes_list[i]->height > h)
        {
            continue;
        }

        num_pixels = modes_list[i]->width * modes_list[i]->height;

        if (num_pixels > best_num_pixels)
        {


            best_mode = modes_list[i];
            best_num_pixels = num_pixels;
        }
    }

    return best_mode;
}
