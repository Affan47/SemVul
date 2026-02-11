get (igzstream& file)
{
    u_int16 i;
    u_int16 nbr_images;
    u_int16 nbr_frames;
    u_int16 t_xoffset, t_yoffset;

    clear ();

    t_xoffset << file;
    t_yoffset << file;


    u_int16 dummy;
    dummy << file;
    dummy << file;


    nbr_images << file;
    for (i = 0; i < nbr_images; i++)
    {
        t_frame.push_back (new image);
        t_frame.back ()->get_raw (file);
    }


    nbr_frames << file;
    animationframe aftemp;

    for (i = 0; i < nbr_frames; i++)
    {
        frame.push_back (aftemp);
        frame.back ().get (file);
    }

    currentframe_ = 0;

    set_offset (t_xoffset, t_yoffset);

    calculate_dimensions ();

    return (0);
}
