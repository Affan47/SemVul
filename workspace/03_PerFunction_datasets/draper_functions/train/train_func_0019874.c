send_spaceship_info(struct player *src, struct conn_list *dest)
{
  int j;

  if (!dest) {
    dest = game.est_connections;
  }

  players_iterate(pplayer) {
    if (!src || pplayer == src) {
      struct packet_spaceship_info info;
      struct player_spaceship *ship = &pplayer->spaceship;

      info.player_num = player_number(pplayer);
      info.sship_state = ship->state;
      info.structurals = ship->structurals;
      info.components = ship->components;
      info.modules = ship->modules;
      info.fuel = ship->fuel;
      info.propulsion = ship->propulsion;
      info.habitation = ship->habitation;
      info.life_support = ship->life_support;
      info.solar_panels = ship->solar_panels;
      info.launch_year = ship->launch_year;
      info.population = ship->population;
      info.mass = ship->mass;
      info.support_rate = ship->support_rate;
      info.energy_rate = ship->energy_rate;
      info.success_rate = ship->success_rate;
      info.travel_time = ship->travel_time;

      for(j=0; j<NUM_SS_STRUCTURALS; j++) {
	info.structure[j] = ship->structure[j] ? '1' : '0';
      }
      info.structure[j] = '\0';

      lsend_packet_spaceship_info(dest, &info);
    }
  } players_iterate_end;
}
