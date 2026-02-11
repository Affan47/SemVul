print()
{
	printf("Path @ %x is:\n", unsigned(long(this)));
	for (unsigned int i = 0; i < depth; i++)
		printf(" %f %f %c\n", x[i], y[i], action[i]);
}
