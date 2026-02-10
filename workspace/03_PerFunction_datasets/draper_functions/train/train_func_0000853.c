compare_vector2(int k, int i, int num)
{
    int j;

    for (j = 0; j < num; j++)
	if (connect_mtr[i][j].next != connect_mtr[k][j].next ||
	    connect_mtr[i][j].cost != connect_mtr[k][j].cost)
	    return 0;

    return 1;
}
