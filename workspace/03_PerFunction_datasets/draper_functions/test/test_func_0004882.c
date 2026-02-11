ComputeTurnStateNeutralPlanet(Planet p) {
  vector<TurnState> state_per_turn;
  int planet_id = p.PlanetID();
  vector<Fleet> fleets = pw->Fleets();
  vector<Fleet> fleets_attacking_planet;
  for(vector<Fleet>::iterator it = fleets.begin(); it < fleets.end(); ++it) {
    if(it->DestinationPlanet() == planet_id)
      fleets_attacking_planet.push_back(*it);
  }
  TurnState first_ts;
  first_ts.owner = 0;
  first_ts.num_ships = p.NumShips();
  state_per_turn.push_back(first_ts);
  for(int turn = 1; turn < 50; turn++) {
    vector<Fleet> fleets_arriving_now;
    for(vector<Fleet>::iterator it = fleets_attacking_planet.begin();
	it < fleets_attacking_planet.end(); ++it) {
      if(it->TurnsRemaining() == turn)
	fleets_arriving_now.push_back(*it);
    }
    state_per_turn.push_back(ComputeNextTurnState(p, state_per_turn[turn-1], fleets_arriving_now));
  }
  return state_per_turn;
}
