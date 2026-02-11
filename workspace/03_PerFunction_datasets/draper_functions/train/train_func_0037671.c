TCurrent(TFP)

int *TFP;
{
    int i,j;

    for(i = 0; i < 3; ++i)
        for(j = 0; j<3; ++j)
            TFP[(3 * i) + j] = Transforms->ttMatrix[i][j];
}
