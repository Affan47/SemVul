shuffle(int size)
{
    int i, j, numswaps, swapnum, temp;

    numswaps = size * 10;

    for (swapnum = 0; swapnum < numswaps; swapnum++) {
	i = rand() % size;
	j = rand() % size;
	temp = deck[i];
	deck[i] = deck[j];
	deck[j] = temp;
    }
}
