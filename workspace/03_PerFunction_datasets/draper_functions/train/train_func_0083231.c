pad (FILE *f, int c)
{
    do
	string (f, " ");
    while (column < c);
    return 0;
}
