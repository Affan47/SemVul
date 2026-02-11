turns_to_reach(game *g, int x, int y)
{
 std::vector<point> path = g->m.route(posx, posy, x, y, has_flag(MF_BASHES));
 if (path.size() == 0)
  return 999;

 double turns = 0.;
 for (int i = 0; i < path.size(); i++) {
  if (g->m.move_cost(path[i].x, path[i].y) == 0)
   turns += 5;
  else
   turns += double(50 * g->m.move_cost(path[i].x, path[i].y)) / speed;
 }
 return int(turns + .9);
}
