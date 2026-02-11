redraw_textcheckbox(struct widget *pCBox)
{
  int ret;
  SDL_Surface *pTheme_Surface, *pIcon;

  ret = (*textcheckbox_baseclass_redraw)(pCBox);
  if (ret != 0) {
    return ret;
  }

  if(!pCBox->string16) {
    return widget_redraw(pCBox);
  }

  pTheme_Surface = pCBox->theme;
  pIcon = create_icon_from_theme(pTheme_Surface, get_wstate(pCBox));

  if (!pIcon) {
    return -3;
  }

  pCBox->theme = pIcon;


  ret = redraw_iconlabel(pCBox);

  FREESURFACE(pIcon);
  pCBox->theme = pTheme_Surface;

  return ret;
}
