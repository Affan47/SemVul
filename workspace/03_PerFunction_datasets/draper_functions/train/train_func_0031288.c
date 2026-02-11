G_sort_histogram_by_count(struct Histogram *histogram)
{
    int n;
    LIST *list;


    if ((n = histogram->num) <= 1)
	return 1;

    list = histogram->list;


    qsort(list, n, sizeof(LIST), &cmp_count);

    return 0;
}
