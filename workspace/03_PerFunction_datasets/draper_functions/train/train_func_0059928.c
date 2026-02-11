CreateIslandLevel(int level, int nPlayers, char const *name)
{
	int xSize, ySize;
	xSize = 20 + (nPlayers + 3) / 4 * 6 - 2;
	ySize = xSize;

	MakeRegions(level, xSize, ySize);

	pRegionArrays[level]->SetName(name);
	pRegionArrays[level]->levelType = ARegionArray::LEVEL_SURFACE;

	MakeCentralLand(pRegionArrays[level]);
	MakeIslands(pRegionArrays[level], nPlayers);
	RandomTerrain(pRegionArrays[level]);

	if (Globals->GROW_RACES) GrowRaces(pRegionArrays[level]);

	FinalSetup(pRegionArrays[level]);
}
