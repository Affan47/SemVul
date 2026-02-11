damroll(int num, int sides)
{
	int i;
	int sum = 0;


	if (sides <= 0) return (0);

	for (i = 0; i < num; i++)
		sum += randint1(sides);

	return (sum);
}
