canvas_put_text(struct canvas *pcanvas, int canvas_x, int canvas_y,
		     enum client_font font, struct color *pcolor,
		     const char *text)
{
  SDL_Surface *pTmp;
  SDL_String16 *pText = create_string16(NULL, 0, *fonts[font]);
  copy_chars_to_string16(pText, text);

  pText->fgcol = *pcolor->color;
  pText->bgcol = (SDL_Color) {0, 0, 0, 0};

  pTmp = create_text_surf_from_str16(pText);

  blit_entire_src(pTmp, pcanvas->surf, canvas_x, canvas_y);

  FREESTRING16(pText);
  FREESURFACE(pTmp);
}
