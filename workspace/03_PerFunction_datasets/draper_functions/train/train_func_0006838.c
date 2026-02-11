Set_clipboard_colors(int nb_colors, T_Components *colors)
{
  Palette_clipboard_count=nb_colors;
  if (nb_colors)
  {
    memcpy(Palette_clipboard, colors, nb_colors*sizeof(T_Components));
  }
}
