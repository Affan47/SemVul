print() const
{
	printf("k=%d\n",k);
	for (unsigned int i = 0; i < size(); i++)
		printf("%d ",operator[](i));
	printf("\n");
}
