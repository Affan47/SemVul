selectionSort(vector<short int> & vec)
{

	short size = vec.size();
	short minIndex = 0;
	for(short i=0; i<size; i++)
	{
		minIndex = i;
		for(short j=i+1; j<size; j++)
		{
			if(vec[j] < vec[minIndex])
				minIndex = j;
		}
		if(i != minIndex)
			xchg(vec[i], vec[minIndex]);
	}
	return;
}
