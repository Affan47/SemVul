Set_green(byte color, short new_color, T_Palette palette)
{
  if (new_color< 0)
    new_color= 0;
  if (new_color>255)
    new_color=255;

  new_color=Round_palette_component(new_color);

  palette[color].G=new_color;
}
