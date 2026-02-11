GIF_new_pixel(T_IO_Context * context, T_GIF_IDB *idb, byte color)
{
  Set_pixel(context, idb->Pos_X+GIF_pos_X, idb->Pos_Y+GIF_pos_Y,color);

  GIF_pos_X++;

  if (GIF_pos_X>=idb->Image_width)
  {
    GIF_pos_X=0;

    if (!GIF_interlaced)
      GIF_pos_Y++;
    else
    {
      switch (GIF_pass)
      {
        case 0 : GIF_pos_Y+=8;
                 break;
        case 1 : GIF_pos_Y+=8;
                 break;
        case 2 : GIF_pos_Y+=4;
                 break;
        default: GIF_pos_Y+=2;
      }

      if (GIF_pos_Y>=idb->Image_height)
      {
        switch(++GIF_pass)
        {
        case 1 : GIF_pos_Y=4;
                 break;
        case 2 : GIF_pos_Y=2;
                 break;
        case 3 : GIF_pos_Y=1;
                 break;
        case 4 : GIF_finished_interlaced_image=1;
        }
      }
    }
  }
}
