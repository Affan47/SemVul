Pixel_in_current_screen      (word x,word y,byte color,int with_preview)
{
    #ifndef NOLAYERS
    byte depth = *(Main_visible_image_depth_buffer.Image+x+y*Main_image_width);
    *(Main_backups->Pages->Image[Main_current_layer] + x+y*Main_image_width)=color;
    if ( depth <= Main_current_layer)
    {
      if (color == Main_backups->Pages->Transparent_color)

        color=*(Main_backups->Pages->Image[depth] + x+y*Main_image_width);

      *(x+y*Main_image_width+Main_screen)=color;

      if (with_preview)
        Pixel_preview(x,y,color);
    }
    #else
    *((y)*Main_image_width+(x)+Main_backups->Pages->Image[Main_current_layer])=color;
    if (with_preview)
        Pixel_preview(x,y,color);
    #endif
}
