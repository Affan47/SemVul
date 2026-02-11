PrintPlanetState(PlanetState* ps) {
  ofstream myfile; myfile.open("output",ios::app);
  Planet p = *(ps->GetPlanet());
  myfile << "PLANET: " << ps->GetPlanet()->PlanetID() <<"\n";
  myfile << "is_unsafe: " << ps->IsUnsafePlanet() << "\n";
  myfile << "is_unsafe_turn: " << ps->GetUnsafeInTurn() << "\n";
  myfile << "available_ships: " << ps->GetAvailableShips() << "\n";
  myfile << "num_ships: " << p.NumShips() << "\n";
  vector<int>* available_ships_per_turn = ps->GetAvailableShipsPerTurn();
  for(int i = 0; i < available_ships_per_turn->size(); ++i)
    myfile << available_ships_per_turn->at(i) << " ";
  myfile << "\n------\n";
  myfile.close();
}
