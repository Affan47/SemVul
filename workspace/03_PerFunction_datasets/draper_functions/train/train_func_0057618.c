ComputeMyFrontierPlanets() {
  vector<int> my_frontier_planets;
  vector<Planet> my_planets = pw->MyPlanets();
  vector<Planet> enemy_planets = pw->EnemyPlanets();
  for(vector<Planet>::iterator it = my_planets.begin(); it < my_planets.end(); ++it) {
    if(IsFrontier(*it, &my_planets, &enemy_planets))
       my_frontier_planets.push_back(it->PlanetID());
  }
  return my_frontier_planets;
}
