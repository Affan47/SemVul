largestproduct (char *numbers)
{
	int temp = 1, largest = 0;
	int index = 0, innerindex = 0;

	for (index = 0; index < 996; index++)
	{
		for (innerindex = index; innerindex <= (index + 4); innerindex++)
		{
			temp = temp * (numbers[innerindex] - '0');
		}

		if (temp > largest) {largest = temp;}
		temp = 1;
	}
	return largest;
}
