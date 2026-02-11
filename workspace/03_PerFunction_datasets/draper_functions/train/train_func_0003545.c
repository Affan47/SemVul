dcraw_image_dimensions(dcraw_data *raw, int flip, int shrink,
                                int *height, int *width)
    {

        *width = raw->width / shrink;
        *height = raw->height / shrink;

        if (raw->fuji_width) {
            int fuji_width = raw->fuji_width / shrink - 1;
            *width = fuji_width / raw->fuji_step;
            *height = (*height - fuji_width) / raw->fuji_step;
        }

        if (raw->pixel_aspect < 1)
            *height = *height / raw->pixel_aspect + 0.5;
        if (raw->pixel_aspect > 1)
            *width = *width * raw->pixel_aspect + 0.5;


        if (flip & 4) {
            int tmp = *height;
            *height = *width;
            *width = tmp;
        }
    }
