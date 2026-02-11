graphics_set_background(Graphics *g, char *SVGserie) {
  Graphics_svg_series *gss;
  Graphics_sprite_anim *anim;
  Graphics_sprite_source *sprites;

  gss = parse_svg_series(SVGserie);
  if (gss == NULL) {
    WARN(_("Couldn't parse SVGserie for background"));
    return FALSE;
  }
  sprites = gss_to_sprite_source(gss);
  anim = draw_sprite_anim(g->background,g->gsize,SS_SCENERY_NORMAL,sprites);
  SDL_FillRect(g->background,NULL,
               SDL_MapRGB(g->background->format,0xcc,0xcc,0xff));
  SDL_BlitSurface(anim->anim[0],NULL,g->background,NULL);
  del_graphics_sprite_anim(anim);
  del_sprite_source(sprites);
  g->background_changed = TRUE;
  return TRUE;
}
