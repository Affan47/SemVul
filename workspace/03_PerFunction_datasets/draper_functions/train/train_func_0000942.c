setCurrentHole(int hole)
{
	if (!holeAction || holeAction->items().count() < hole)
		return;

	holeAction->setCurrentItem(hole - 1);
}
