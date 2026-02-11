eraseSelection(bool insertMode)
{
	int y1, y2, x1, x2, i;

	if (!selector)
		return;

	getSelection(&y1, &x1, &y2, &x2, false);
	selector = NULL;
	if (!insertMode)
		remove(y1, x1, y2, x2);
	else
	{
		begin();
		for (i = y1; i <= y2; i++)
			remove(i, x1, i, x2);
		end();
	}
}
