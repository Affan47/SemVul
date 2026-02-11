HasConnectingRoad(int realDirection)
{
	int opposite = GetRealDirComp(realDirection);

	if (neighbors[realDirection]
			&& neighbors[realDirection]->HasExitRoad(opposite))
		return 1;

	return 0;
}
