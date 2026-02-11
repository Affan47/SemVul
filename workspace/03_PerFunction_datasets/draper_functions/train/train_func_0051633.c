GIF_next_pixel(T_IO_Context *context, T_GIF_IDB *idb)
  {
    byte temp;

    temp=Get_pixel(context, GIF_pos_X,GIF_pos_Y);

    if (++GIF_pos_X>=idb->Image_width)
    {
      GIF_pos_X=0;
      if (++GIF_pos_Y>=idb->Image_height)
        GIF_stop=1;
    }

    return temp;
  }
