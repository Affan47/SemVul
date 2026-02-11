assigned_missions_value(game *g)
{
 int ret = 0;
 for (int i = 0; i < chatbin.missions_assigned.size(); i++)
  ret += g->find_mission(chatbin.missions_assigned[i])->value;
 return ret;
}
