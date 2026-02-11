InitCombination(void)
{
    unsigned int i, j;

    for (i = 0; i < MAX_N; i++)
        anCombination[i][0] = i + 1;

    for (j = 1; j < MAX_R; j++)
        anCombination[0][j] = 0;

    for (i = 1; i < MAX_N; i++)
        for (j = 1; j < MAX_R; j++)
            anCombination[i][j] = anCombination[i - 1][j - 1] + anCombination[i - 1][j];

    fCalculated = 1;
}
