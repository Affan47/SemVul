getat()
{
	int place = 0;
	while (place < len && (str[place] == ' ' || str[place] == '\t'))
		place++;
	if (place >= len) return 0;
	if (str[place] == '@') {
		str[place] = ' ';
		return 1;
	}
	return 0;
}
