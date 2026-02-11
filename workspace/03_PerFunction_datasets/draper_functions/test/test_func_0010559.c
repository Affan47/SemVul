emowse_hit_sort(const void *a, const void *b)
{
    double x;
    double y;

    x = (*(PHits const *)a)->score;
    y = (*(PHits const *)b)->score;

    if(x==y)
	return 0;
    else if(x<y)
	return -1;

    return 1;
}
