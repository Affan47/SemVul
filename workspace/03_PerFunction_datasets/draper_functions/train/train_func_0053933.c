operator= (const npc &rhs)
{
 id = rhs.id;
 name = rhs.name;
 attitude = rhs.attitude;
 wandx = rhs.wandx;
 wandy = rhs.wandy;
 wandf = rhs.wandf;
 omx = rhs.omx;
 omy = rhs.omy;
 omz = rhs.omz;
 mapx = rhs.mapx;
 mapy = rhs.mapy;
 plx = rhs.plx;
 ply = rhs.ply;
 plt = rhs.plt;
 itx = rhs.itx;
 ity = rhs.ity;
 goalx = rhs.goalx;
 goaly = rhs.goaly;
 fetching_item = rhs.fetching_item;
 has_new_items = rhs.has_new_items;
 worst_item_value = rhs.worst_item_value;
 fac_id = rhs.fac_id;
 my_fac = rhs.my_fac;
 mission = rhs.mission;
 personality = rhs.personality;
 op_of_u = rhs.op_of_u;
 flags = rhs.flags;
 posx = rhs.posx;
 posy = rhs.posy;
 chatbin = rhs.chatbin;
 myclass = rhs.myclass;

 weapon = rhs.weapon;
 inv = rhs.inv;
 worn.clear();
 for (int i = 0; i < rhs.worn.size(); i++)
  worn.push_back(rhs.worn[i]);

 needs.clear();
 for (int i = 0; i < rhs.needs.size(); i++)
  needs.push_back(rhs.needs[i]);

 path.clear();
 for (int i = 0; i < rhs.path.size(); i++)
  path.push_back(rhs.path[i]);

 for (int i = 0; i < num_hp_parts; i++) {
  hp_cur[i] = rhs.hp_cur[i];
  hp_max[i] = rhs.hp_max[i];
 }

 marked_for_death = rhs.marked_for_death;

 return *this;
}
