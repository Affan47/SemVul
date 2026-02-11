flamethrower(game *g, monster *z)
{
 int t;
 if (abs(g->u.posx - z->posx) > 5 || abs(g->u.posy - z->posy) > 5 ||
     !g->sees_u(z->posx, z->posy, t))
  return;
 z->sp_timeout = z->type->sp_freq;
 z->moves = -500;
 std::vector<point> traj = line_to(z->posx, z->posy, g->u.posx, g->u.posy, t);
 for (int i = 0; i < traj.size(); i++)
  g->m.add_field(g, traj[i].x, traj[i].y, fd_fire, 1);
 g->u.add_disease(DI_ONFIRE, 8, g);
}
