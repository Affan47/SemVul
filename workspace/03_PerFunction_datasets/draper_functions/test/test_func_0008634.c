mission_failure(game *g, npc *p)
{
 int selected = p->chatbin.mission_selected;
 if (selected == -1 || selected >= p->chatbin.missions_assigned.size()) {
  debugmsg("mission_selected = %d; missions_assigned.size() = %d!",
           selected, p->chatbin.missions_assigned.size());
  return;
 }
 g->mission_failed(p->chatbin.missions_assigned[selected]);
}
