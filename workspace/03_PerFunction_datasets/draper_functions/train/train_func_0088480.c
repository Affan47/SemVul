moveWithPlatform()
{
  int py;
  int old_speed;
  int diff, dir;

  if(!cursor.platform)
    return 0;


  py = cursor.platform->pos_y * TILE_H + cursor.platform->pixel_y;
  if(cursor.platform->dir == DIR_UP) {
    py -= cursor.platform->speed_y + map.max_speed_boost;
  } else if(cursor.platform->dir == DIR_DOWN) {
    py += cursor.platform->speed_y + map.max_speed_boost;
  }
  diff = py - (cursor.pos_y * TILE_H + tom[0]->h + cursor.pixel_y);
  dir = (diff > 0 ? DIR_DOWN : DIR_UP);
  if(diff) {
    old_speed = cursor.speed_y;
    cursor.speed_y = (abs(diff) < TILE_H ? abs(diff) : TILE_H);
    if(dir == DIR_UP)
      moveUp(1, 1);
    else
      moveDown(1, 1, 0);
    cursor.speed_y = old_speed;
  }

  if(cursor.platform->monster->type == MONSTER_PLATFORM) {
    old_speed = cursor.speed_x;
    cursor.speed_x = cursor.platform->speed_x + map.max_speed_boost;
    if(cursor.platform->dir == DIR_LEFT)
      moveLeft(1);
    else
      moveRight(1);
    cursor.speed_x = old_speed;
  }

  return 1;
}
