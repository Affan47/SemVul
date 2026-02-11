getposition()
{
    for ( int i=1; i<gridX-1; i++)
        for ( int j=1;j<gridY-1; j++)

			posit[i][j] = MAX(-1e20, MIN(1e20, posit[i][j]+veloc[i][j]));
}
