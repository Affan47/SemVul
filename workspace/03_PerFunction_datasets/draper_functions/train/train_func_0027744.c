get_distance_and_dir_nosmooth(int h, int h1, int *dir)
{
  int distancex = 5000;
  int distancey = 5000;


  int dirx = 6;
  int diry = 6;

  if ((spr[h].x > spr[h1].x) && ((spr[h].x - spr[h1].x) < distancex))
    {
      distancex = spr[h].x - spr[h1].x;
      dirx = 4;
    }
  if ((spr[h].x < spr[h1].x) && ((spr[h1].x - spr[h].x) < distancex))
    {
      distancex = spr[h1].x - spr[h].x;
      dirx = 6;
    }

  if ((spr[h].y > spr[h1].y) && ((spr[h].y - spr[h1].y) < distancey))
    {
      distancey = spr[h].y - spr[h1].y;
      diry = 8;
    }
  if ((spr[h].y < spr[h1].y) && ((spr[h1].y - spr[h].y) < distancey))
    {
      distancey = spr[h1].y - spr[h].y;
      diry = 2;
    }

  if (distancex > distancey)
    {
      *dir = dirx;
      return distancex;
    }
  else
    {
      *dir = diry;
      return distancey;
    }
}
