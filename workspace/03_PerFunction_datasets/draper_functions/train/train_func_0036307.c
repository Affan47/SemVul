update_drawing_info(void *data, void *user_data) {
  Model_object *m = (Model_object *) data;
  Graphics *g = (Graphics *) user_data;
  Graphics_object *go;
  SDL_Surface *sprite;
  SDL_Rect rect;

  go = model_object_get_gfx_data(m);
  if (go == NULL && m->gfx_state == GFX_DELETED) {
    return TRUE;
  }

  if (go == NULL) {
    go = new_graphics_object(g,m);
    model_object_set_gfx_data(m,go);
	}

	if (go->pinfo != NULL) {
		update_player_info(go->pinfo,g,m,go);
	}

  if (m->gfx_state == GFX_DELETED) {
    if (go->dinfo->cur.w > 0) {
      rect = go->dinfo->cur;
      rect.x -= g->goffset->x;
      rect.y -= g->goffset->y;
      graphics_add_rect_update(g,go->dinfo->cur);
      SDL_BlitSurface(g->background,&rect,
                      g->screen,&(go->dinfo->cur));
    }
    del_graphics_object(go, g);
    model_object_set_gfx_data(m,NULL);
    return TRUE;
  }

  graphics_drawinfo_set_pos(go->dinfo,g,m->pos,go->size);
  sprite = graphics_cache_getnext_sprite(go->scache,g,go,m);
  graphics_drawinfo_setsprite(go->dinfo,sprite);
  return TRUE;
}
