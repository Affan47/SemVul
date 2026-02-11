drawMapBottomEdge()
{
  MapDrawParams params;
  SDL_Rect pos;
  int n, m, level, x, y;

  pos.x = 0;
  pos.y = map.level[0]->h - cursor.speed_y;
  pos.w = map.level[0]->w;
  pos.h = cursor.speed_y;
  for(level = LEVEL_BACK; level < LEVEL_COUNT - 1; level++) {
    SDL_FillRect(map.level[level], &pos,
                 SDL_MapRGBA(screen->format, 0x00, 0x00, 0x00, 0x00));
  }


  getMapDrawParams(&params);


  params.end_y = (cursor.pos_y - screen_center_y) + screen_h;


  for(level = LEVEL_BACK; level < LEVEL_COUNT - 1; level++) {


    for(y = params.end_y - EXTRA_Y; y <= params.end_y; y++) {
      if(params.end_y >= map.h)
        break;
      for(x = params.start_x; x < params.end_x;) {
        n = (map.image_index[level][x + (y * map.w)]);
        if(map.monsters) {
          m = isMonsterImage(n);
          if(m > -1) {
            addLiveMonster(m, n, x, y);
            continue;
          }
        }
        if(n != EMPTY_MAP) {


          pos.x = (params.offset_x + (x - params.start_x)) * TILE_W;
          pos.y =
            (map.level[level]->h - ((params.end_y - y) * TILE_H)) -
            cursor.pixel_y;
          pos.w = images[n]->image->w;
          pos.h = images[n]->image->h;


          pos.x += (EXTRA_X * TILE_W) - cursor.pixel_x;

          SDL_BlitSurface(images[n]->image, NULL, map.level[level], &pos);

          x += images[n]->image->w / TILE_W;
        } else {
          x++;
        }
      }
    }
  }
}
