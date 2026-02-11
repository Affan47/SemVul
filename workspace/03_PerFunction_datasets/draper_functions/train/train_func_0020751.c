long_term_goal_action(game *g)
{
 if (g->debugmon)
  debugmsg("long_term_goal_action()");
 path.clear();

 if (mission == NPC_MISSION_SHOPKEEP || mission == NPC_MISSION_SHELTER)
  return npc_pause;


 if (!has_destination())
  set_destination(g);
 return npc_goto_destination;

 return npc_undecided;
}
