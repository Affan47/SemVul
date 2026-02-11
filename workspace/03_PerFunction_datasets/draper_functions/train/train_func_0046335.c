ComputeShipsAvailablePerTurnBasedOnGrowthRate(vector<int> ships_per_turn,
									     Planet p) {
  int turns_same_owner = 0;
  for(int i = 1; i < 50; i++) {
    if((ships_per_turn[i-1] > 0 && ships_per_turn[i-1] < 0) ||
       (ships_per_turn[i-1] < 0 && ships_per_turn[i-1] > 0)) turns_same_owner = 0;
    turns_same_owner++;
    if(ships_per_turn[i-1] > 0) ships_per_turn[i] += p.GrowthRate() * turns_same_owner;
    else if(ships_per_turn[i-1] < 0) ships_per_turn[i] -= p.GrowthRate() * turns_same_owner;
  }
  return ships_per_turn;
}
