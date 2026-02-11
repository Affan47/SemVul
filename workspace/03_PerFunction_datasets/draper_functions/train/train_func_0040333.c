FindClosestEnemyFromMyPlanet(Planet p, vector<Planet>* enemy_planets) {
  int min_distance_to_enemy = 1000;
  int closest_enemy_planet = 1;
  for(vector<Planet>::iterator it = enemy_planets->begin(); it < enemy_planets->end(); ++it) {
    int aux_distance = pw->Distance(p.PlanetID(), it->PlanetID());
    if(aux_distance < min_distance_to_enemy) {
      min_distance_to_enemy = aux_distance;
      closest_enemy_planet = it->PlanetID();
    }
  }
  return pair<int,int>(closest_enemy_planet, min_distance_to_enemy);
}
