percent_pos(pos, percent)
	POSITION pos;
	int percent;
{
	POSITION result100;

	if (percent == 0)
		return (0);
	else if ((result100 = pos * percent) / percent == pos)
		return (result100 / 100);
	else
		return (percent * (pos / 100));
}
