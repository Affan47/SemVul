GetCurrentSearch(void)
{
	if(currentSearchIdx >= searchListLength)
		currentSearchIdx = searchListLength - 1;
	if(currentSearchIdx < 0)
		currentSearchIdx = 0;

	return &searchList[currentSearchIdx];
}
