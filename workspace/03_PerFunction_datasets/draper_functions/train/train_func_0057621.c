canvas_fog_sprite_area(struct canvas *pcanvas, struct sprite *psprite,
			    int canvas_x, int canvas_y)
{
  SDL_Rect dst = {canvas_x, canvas_y, GET_SURF(psprite)->w,
                                      GET_SURF(psprite)->h};

  SDL_Surface *tmp_surf = create_surf_alpha(GET_SURF(psprite)->w,
                                            GET_SURF(psprite)->h,
                                            SDL_SWSURFACE);
  SDL_FillRect(tmp_surf, NULL, SDL_MapRGBA(tmp_surf->format, 0, 0, 0, 64));
  alphablit(tmp_surf, NULL, pcanvas->surf, &dst);
  FREESURFACE(tmp_surf);
}
