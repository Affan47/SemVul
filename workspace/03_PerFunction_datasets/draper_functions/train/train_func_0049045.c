CountConnectingRoads()
{
	int connections = 0;
	for (int i = 0; i < NDIRS; i++) {
		if (HasExitRoad(i) && neighbors[i] &&
				HasConnectingRoad(i))
			connections ++;
	}
	return connections;
}
