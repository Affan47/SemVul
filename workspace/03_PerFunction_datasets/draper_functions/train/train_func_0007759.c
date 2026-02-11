moveGravity()
{
  int old_speed;

  if(!map.gravity || interact.on_ladder || cursor.platform) {
    return;
  }

  old_speed = cursor.speed_y;
  cursor.speed_y = GRAVITY_SPEED + map.max_speed_boost;
  cursor.gravity = 1;
  cursor.gravity = moveDown(1, 0, 0);
  cursor.gravity = 0;
  cursor.speed_y = old_speed;
}
