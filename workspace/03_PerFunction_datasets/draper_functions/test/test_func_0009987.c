generate_logic_screen_descriptor(gif_logic_screen_descriptor *lsd, uint16 width, uint16 height)
{
    lsd->logic_screen_width = width;
    lsd->logic_screen_height = height;
    if(GIF_ENC_TYPE_GREYSCALE == enc.settings.enc_type
       || GIF_ENC_TYPE_SEPIA == enc.settings.enc_type)
    {
        lsd->global_color_table_flag = 1;
    }
    else
    {

        lsd->global_color_table_flag = 0;
    }

    lsd->color_resolution = 7;
    lsd->sort_flag = 0;
    lsd->size_of_color_table = 7;
    lsd->background_color_index = 0;
    lsd->pixel_aspect_ratio = 0;


    enc.global_color_table_flag = lsd->global_color_table_flag;

}
