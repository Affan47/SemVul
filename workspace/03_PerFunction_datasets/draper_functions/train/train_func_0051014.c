addLineToIndex(int index)
{
	if (lineList[index] == true)
	{
		kWarning() << "KSquaresGame::addLineToIndex():"
				   << "trying to add line already there!";
		return;
	}
	lineList[index] = true;
	lastLine = index;

	emit drawLine(index, Settings::lineColor());

	if (gameInProgress)
		checkForNewSquares();
}
