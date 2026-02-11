cardToChar (int rank)
{
	char ret = 0;
	char *temp = (char *) malloc(sizeof(char)*2);
	if ((rank>0)&&(rank < 10)) sprintf(temp, "%d", rank);
	else if (rank == 10) ret = 'T';
	else if (rank == 11) ret = 'J';
	else if (rank == 12) ret = 'Q';
	else if (rank == 13) ret = 'K';
	else if (rank == 14) ret = 'A';
	else ret = temp[0];
	free(temp);
	return ret;
}
