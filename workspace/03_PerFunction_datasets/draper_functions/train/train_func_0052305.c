set_man_gravity_origin(WinManager *man)
{
  if (man->gravity == NorthWestGravity || man->gravity == NorthEastGravity)
    man->geometry.gravity_y = 0;
  else
    man->geometry.gravity_y = man->geometry.height;
  if (man->gravity == NorthWestGravity || man->gravity == SouthWestGravity)
    man->geometry.gravity_x = 0;
  else
    man->geometry.gravity_x = man->geometry.width;
}
