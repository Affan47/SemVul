shift(int sx, int sy)
{
 posx -= sx * SEEX;
 posy -= sy * SEEY;
 for (int i = 0; i < plans.size(); i++) {
  plans[i].x -= sx * SEEX;
  plans[i].y -= sy * SEEY;
 }
}
