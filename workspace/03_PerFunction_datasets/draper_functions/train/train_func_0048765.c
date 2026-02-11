compareFunctionGenerate(int i, int j)
{
	if(nConflActivitiesL[currentLevel][i] < nConflActivitiesL[currentLevel][j] ||
	 (nConflActivitiesL[currentLevel][i] == nConflActivitiesL[currentLevel][j] &&
	 nMinDaysBrokenL[currentLevel][i] < nMinDaysBrokenL[currentLevel][j]))
		return true;

	return false;
}
